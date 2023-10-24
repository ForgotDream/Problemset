/**
 * @file    P4345 [SHOI2015] 超能粒子炮·改.cpp
 * @author  ForgotDream
 * @brief   Math
 * @date    2023-08-11
 */
#include <bits/stdc++.h>
using i64 = long long;
constexpr int N = 2550, mod = 2333;
int t, c[N][N], g[N][N];
i64 n, p;
void init() {
  for (int i = 0; i <= 2500; i++) {
    for (int j = 0; j <= 2500; j++) {
      if (!j) c[i][j] = 1;
      else (c[i][j] = c[i - 1][j - 1] + c[i - 1][j]) %= mod;
      (g[i][j] = g[i][j - 1] + c[i][j]) %= mod;
    }
  }
}
int lucas(i64 n, i64 m) {
  if (!m) return 1;
  return c[n % mod][m % mod] * lucas(n / mod, m / mod) % mod;
}
int f(i64 n, i64 k) {
  if (n <= 2500 && k <= 2500) return g[n][k];
  if (!n || !k) return 1;
  if (k < 0) return 0;
  return (g[n % mod][mod - 1] * f(n / mod, k / mod - 1) % mod +
          lucas(n / mod, k / mod) * g[n % mod][k % mod] % mod) %
         mod;
}
void solve() {
  std::cin >> n >> p;
  std::cout << f(n, p) << "\n";
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  init();
  std::cin >> t;
  while (t--) solve();
  return 0;
}