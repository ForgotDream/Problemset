/*
 * @file    P6091 【模板】原根.cpp
 * @author  ForgotDream
 * @brief   Primitive Root
 * @date    2024-02-01
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

// primitive root

constexpr int N = 1e6 + 50;

int prime[N], cnt;
int phi[N], mpf[N];  // `mpf` stands for min prime factor
bool is_not_prime[N];
bool has_root[N];

void init(int _n) {
  phi[1] = 1;
  for (int i = 2; i <= _n; i++) {
    if (!is_not_prime[i]) {
      prime[++cnt] = i, phi[i] = i - 1;
      mpf[i] = i;
    }
    for (int j = 1; j <= cnt && i * prime[j] <= _n; j++) {
      is_not_prime[i * prime[j]] = true;
      phi[i * prime[j]] = phi[i] * phi[prime[j]];
      mpf[i * prime[j]] = prime[j];
      if (i % prime[j] == 0) {
        phi[i * prime[j]] = phi[i] * prime[j];
        mpf[i * prime[j]] = mpf[i];
        break;
      }
    }
  }

  has_root[2] = has_root[4] = true;
  for (int i = 2; i <= cnt; i++) {
    for (i64 j = prime[i]; j <= _n; j *= prime[i]) has_root[j] = true;
    for (i64 j = 2 * prime[i]; j <= _n; j *= prime[i]) has_root[j] = true;
  }
}

inline i64 fast_pow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}

int n, d;

int factor[N], fcnt;

bool check(int u) {
  if (fast_pow(u, phi[n], n) != 1) return false;
  for (int i = 1; i <= fcnt; i++) {
    if (fast_pow(u, phi[n] / factor[i], n) == 1) return false;
  }
  return true;
}

void solve() {
  std::cin >> n >> d, fcnt = 0;

  if (!has_root[n]) {
    std::cout << "0\n\n";
    return;
  }

  int copy = phi[n];
  while (copy != 1) {
    int cur = mpf[copy];
    if (cur != factor[fcnt]) factor[++fcnt] = cur;
    copy /= cur;
  }

  int mpr = 1;  // `mpr` stands for min primitive root
  while (!check(mpr)) mpr++;

  std::vector<int> pr;
  i64 prod = 1;
  for (int i = 1; i <= phi[n]; i++) {
    prod = prod * mpr % n;
    if (std::gcd(phi[n], i) == 1) pr.push_back(prod);
  }
  std::sort(pr.begin(), pr.end());

  std::cout << pr.size() << "\n";
  for (int i = 1; i <= int(pr.size()) / d; i++) {
    std::cout << pr[i * d - 1] << " ";
  }
  std::cout << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  init(1e6);

  int t = 1;
  std::cin >> t;
  while (t--) solve();

  return 0;
}
