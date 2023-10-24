/**
 * @file    AT_arc157_c [ARC157C] YY Square.cpp
 * @author  ForgotDream
 * @brief   DP + Math
 * @date    2023-07-30
 */
#include <bits/stdc++.h>
#include <atcoder/modint.hpp>

using i64 = long long;
using Z = atcoder::modint998244353;

constexpr int N = 2050;
int n, m;
char a[N][N];
// f -> sum, g -> square
Z f[N][N], g[N][N];
Z fact[2 * N];

Z C(int n, int m) { return fact[n] * fact[m].inv() * fact[n - m].inv(); }

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      std::cin >> a[i][j];
    }
  }

  fact[0] = 1;
  for (int i = 1; i <= n + m; i++) fact[i] = fact[i - 1] * i;

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (a[i][j] == 'Y') {
        if (a[i - 1][j] == 'Y') {
          auto tmp = C(i + j - 3, i - 2);
          f[i][j] += f[i - 1][j] + tmp;
          g[i][j] += g[i - 1][j] + 2 * f[i - 1][j] + tmp;
        } else {
          f[i][j] += f[i - 1][j];
          g[i][j] += g[i - 1][j];
        }
        if (a[i][j - 1] == 'Y') {
          auto tmp = C(i + j - 3, j - 2);
          f[i][j] += f[i][j - 1] + tmp;
          g[i][j] += g[i][j - 1] + 2 * f[i][j - 1] + tmp;
        } else {
          f[i][j] += f[i][j - 1];
          g[i][j] += g[i][j - 1];
        }
      } else {
        f[i][j] = f[i - 1][j] + f[i][j - 1];
        g[i][j] = g[i - 1][j] + g[i][j - 1];
      }
    }
  }

  std::cout << g[n][m].val() << "\n";

  return 0;
}