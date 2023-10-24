/**
 * @file    CF213C Relay Race.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-06-27
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int inf = 1e9;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  
  int n;
  std::cin >> n;

  std::vector a(n, std::vector<int>(n));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      std::cin >> a[i][j];
    }
  }

  std::vector f(2 * n, std::vector(n, std::vector<int>(n, -inf)));
  f[0][0][0] = 0;
  for (int i = 1; i < 2 * n; i++) {
    for (int y1 = 0; y1 < std::min(n, i); y1++) {
      for (int y2 = 0; y2 < std::min(n, i); y2++) {
        int x1 = i - y1 - 1, x2 = i - y2 - 1;
        if (x1 >= n || x2 >= n) {
          continue;
        }
        f[i][y1][y2] = a[x1][y1] + a[x2][y2] + std::max({
          f[i - 1][y1][y2],
          (y1 ? f[i - 1][y1 - 1][y2] : -inf),
          (y2 ? f[i - 1][y1][y2 - 1] : -inf),
          ((y1 && y2) ? f[i - 1][y1 - 1][y2 - 1] : -inf)
        });
        if (y1 == y2) {
          f[i][y1][y2] -= a[x1][y1];
        }
      }
    }
  }

  std::cout << f[2 * n - 1][n - 1][n - 1] << "\n";

  return 0;
}
