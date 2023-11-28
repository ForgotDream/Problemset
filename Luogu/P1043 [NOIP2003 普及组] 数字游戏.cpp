/**
 * @file    P1043 [NOIP2003 普及组] 数字游戏.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-11-26
 */
#include <bits/stdc++.h>

using i64 = int64_t;

constexpr int N = 105, M = 15, SIG = 10;
int n, m, a[N];
i64 f[N][N][M], g[N][N][M];
void solve() {
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) std::cin >> a[i], a[i + n] = a[i];
  memset(g, 0x3f, sizeof(g));
  for (int l = 1; l <= 2 * n; l++) {
    for (int r = l; r <= 2 * n; r++) {
      f[l][r][1] = g[l][r][1] = ((f[l][r - 1][1] + a[r]) % SIG + SIG) % SIG;
    }
  }
  for (int k = 2; k <= m; k++) {
    for (int l = 1; l <= n; l++) {
      for (int r = l + k - 1; r <= l + n - 1; r++) {
        for (int p = l + k - 2; p < r; p++) {
          f[l][r][k] = std::max(f[l][r][k], f[l][p][k - 1] * f[p + 1][r][1]);
          g[l][r][k] = std::min(g[l][r][k], g[l][p][k - 1] * g[p + 1][r][1]);
        }
      }
    }
  }
  i64 max = 0, min = 1e18;
  for (int i = 1; i <= n; i++) {
    max = std::max(max, f[i][i + n - 1][m]);
    min = std::min(min, g[i][i + n - 1][m]);
  }
  std::cout << min << "\n" << max << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
