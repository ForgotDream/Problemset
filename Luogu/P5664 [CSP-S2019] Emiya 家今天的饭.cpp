/**
 * @file    P5664 [CSP-S2019] Emiya 家今天的饭.cpp
 * @author  ForgotDream
 * @brief   Math
 * @date    2023-08-15
 */
#include <bits/stdc++.h>
using i64 = long long;
constexpr int N = 105, M = 2050, mod = 998244353;
int n, m, a[N][M], sum[N];
i64 f[N][2 * N], g[N][N];
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      std::cin >> a[i][j];
      (sum[i] += a[i][j]) %= mod;
    }
  }
  i64 ans = 0;
  for (int k = 1; k <= m; k++) {
    std::memset(f, 0, sizeof(f));
    f[0][n] = 1;
    for (int i = 1; i <= n; i++) {
      for (int j = n - i; j <= n + i; j++) {
        f[i][j] = (f[i - 1][j] + f[i - 1][j - 1] * a[i][k] % mod +
                   f[i - 1][j + 1] * (sum[i] - a[i][k] + mod) % mod) %
                  mod;
      }
    }
    for (int i = 1; i <= n; i++) (ans += f[n][n + i]) %= mod;
  }
  g[0][0] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= n; j++) {
      g[i][j] = g[i - 1][j];
      if (j) (g[i][j] += g[i - 1][j - 1] * sum[i]) %= mod;
    }
  }
  for (int i = 1; i <= n; i++) (ans -= g[n][i] - mod) %= mod;
  std::cout << ans * (mod - 1) % mod << "\n";
  return 0;
}