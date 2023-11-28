/**
 * @file    P1437 [HNOI2004] 敲砖块.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-11-27
 */
#include <bits/stdc++.h>

using i64 = int64_t;

constexpr int N = 55, M = 1500;
int n, m, mx[N][M], s[N][N], f[N][M];
void solve() {
  std::cin >> n >> m;
  for (int j = 1; j <= n; j++) {
    for (int i = n, u; i >= j; i--) std::cin >> u, s[i][j] = s[i][j - 1] + u;
  }
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = i; j >= 1; j--) {
      for (int k = std::min(j + i * (i - 1) / 2, m); k >= j * (j + 1) / 2;
           k--) {
        f[j][k] = mx[j - 1][k - j] + s[i][j];
        mx[j][k] = std::max(mx[j + 1][k], f[j][k]);
        ans = std::max(ans, f[j][k]);
      }
    }
    for (int k = i * (i - 1) / 2 + 1; k <= i * (i + 1) / 2; k++) {
      for (int j = k - i * (i - 1) / 2 - 1; ~j; j--) {
        mx[j][k] = std::max(mx[j + 1][k], f[j][k]);
      }
    }
    for (int k = 1; k <= i * (i + 1) / 2; k++) {
      mx[0][k] = std::max(mx[1][k], mx[0][k]);
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
