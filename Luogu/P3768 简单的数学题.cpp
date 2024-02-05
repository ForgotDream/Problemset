/*
 * @file    P3768 简单的数学题.cpp
 * @author  ForgotDream
 * @brief   Math
 * @date    2024-02-05
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 1e7 + 50;

i64 n, p;

inline i64 fast_pow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}

int prime[N], cnt, lim = 1e7;
i64 phi[N], s_phi[N];
bool is_not_prime[N];

void init(int _n) {
  phi[1] = 1;
  for (int i = 2; i <= _n; i++) {
    if (!is_not_prime[i]) prime[++cnt] = i, phi[i] = i - 1;
    for (int j = 1; j <= cnt && 1ll * i * prime[j] <= _n; j++) {
      int d = i * prime[j];
      is_not_prime[d] = true, phi[d] = phi[i] * phi[prime[j]];
      if (i % prime[j] == 0) {
        phi[d] = phi[i] * prime[j];
        break;
      }
    }
  }

  for (int i = 1; i <= _n; i++) {
    s_phi[i] = (s_phi[i - 1] + phi[i] * i % p * i % p) % p;
  }
}

i64 inv6, inv2;

inline i64 calc_s2(i64 u) {
  return u % p * (u + 1) % p * (2 * u % p + 1) % p * inv6 % p;
}

inline i64 calc_s3(i64 u) {
  i64 s1 = u % p * (u + 1) % p * inv2 % p;
  return s1 * s1 % p;
}

std::unordered_map<i64, i64> mp_phi;

i64 calc(i64 u) {
  if (u <= lim) return s_phi[u];
  if (mp_phi.count(u)) return mp_phi[u];

  i64 res = calc_s3(u);
  for (i64 i = 2, j; i <= u; i = j + 1) {
    j = u / (u / i);
    res = (res - (calc_s2(j) - calc_s2(i - 1) + p) % p * calc(u / i) % p) % p;
    res = (res + p) % p;
  }

  return mp_phi[u] = res;
}

void solve() {
  std::cin >> p >> n;

  init(lim);

  inv2 = (p + 1) / 2, inv6 = fast_pow(6, p - 2, p);

  i64 ans = 0;
  for (i64 i = 1, j; i <= n; i = j + 1) {
    j = n / (n / i);
    ans = (ans + (calc(j) - calc(i - 1) + p) % p * calc_s3(n / i) % p) % p;
  }

  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
