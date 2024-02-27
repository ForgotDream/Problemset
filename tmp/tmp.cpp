/*
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2024-02-26
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 550, LIM = 1 << 8, MASK = LIM - 1;

int n;
i64 p;

int prime[N], min_fac[N], cnt, to[N];
bool is_not_prime[N];

i64 f[LIM][LIM], g[LIM][LIM], h[LIM][LIM];

void get_prime() {
  for (int i = 2; i <= n; i++) {
    if (!is_not_prime[i]) to[i] = cnt, prime[++cnt] = i, min_fac[i] = i;
    for (int j = 1; j <= cnt && i * prime[j] <= n; j++) {
      is_not_prime[i * prime[j]] = true;
      min_fac[i * prime[j]] = prime[j];
      if (i % prime[j] == 0) {
        min_fac[i * prime[j]] = min_fac[i];
        break;
      }
    }
  }
}

int pset[N], extra[N];
std::vector<int> bln[N];

void solve() {
  std::cin >> n >> p;

  get_prime();
  for (int i = 2; i <= n; i++) {
    int j = i / min_fac[i];
    pset[i] = pset[j], extra[i] = extra[j];
    if (min_fac[i] > 22) extra[i] = min_fac[i];
    else pset[i] |= 1 << to[min_fac[i]];
    bln[extra[i]].push_back(pset[i]);
    std::cerr << pset[i] << " " << extra[i] << "\n";
  }

  f[0][0] = 1;
  for (int i = 0; i <= n; i++) {
    if (bln[i].empty()) continue;
    
    memcpy(g, f, sizeof(f)), memcpy(h, f, sizeof(f));
    for (auto s : bln[i]) {
      for (int j = MASK; ~j; j--) {
        int rev = MASK - j;
        for (int k = rev;; k = (k - 1) & rev) {
          if (!(s & j)) (h[j][k | s] += h[j][k]) %= p;
          if (!(s & k)) (g[j | s][k] += g[j][k]) %= p;
          if (!k) break;
        }
      }
    }

    for (int j = 0; j < LIM; j++) {
      int rev = MASK - j;
      for (int k = rev;; k = (k - 1) & rev) {
        f[j][k] = (g[j][k] + h[j][k] - f[j][k] + p) % p;
        if (!k) break;
      }
    }
  }

  i64 ans = 0;
  for (int j = 0; j < LIM; j++) {
    int rev = MASK - j;
    for (int k = rev;; k = (k - 1) & rev) {
      (ans += f[j][k]) %= p;
      if (!k) break;
    }
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
