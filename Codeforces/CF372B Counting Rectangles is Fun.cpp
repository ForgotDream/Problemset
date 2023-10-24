/**
 * @file    CF372B Counting Rectangles is Fun.cpp
 * @author  ForgotDream
 * @brief   高位前缀和
 * @date    2023-08-23
 */
#include <iostream>

using i64 = long long;

constexpr int N = 50;
int n, m, q, a[N][N], ans[N][N][N][N];
void solve() {
  std::cin >> n >> m >> q;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      char c;
      std::cin >> c;
      a[i][j] = c - '0';
      a[i][j] += a[i][j - 1] + a[i - 1][j] - a[i - 1][j - 1];
    }
  }
  for (int x1 = 1; x1 <= n; x1++) {
    for (int y1 = 1; y1 <= m; y1++) {
      for (int x2 = x1; x2 <= n; x2++) {
        for (int y2 = y1; y2 <= m; y2++) {
          if (a[x2][y2] - a[x1 - 1][y2] - a[x2][y1 - 1] + a[x1 - 1][y1 - 1] ==
              0) {
            ans[x1][y1][x2][y2]++;
          }
        }
      }
    }
  }
  for (int x1 = n; x1 >= 1; x1--) {
    for (int y1 = m; y1 >= 1; y1--) {
      for (int x2 = 1; x2 <= n; x2++) {
        for (int y2 = 1; y2 <= m; y2++) {
          ans[x1][y1][x2][y2] += ans[x1 + 1][y1][x2][y2];
        }
      }
    }
  }
  for (int x1 = n; x1 >= 1; x1--) {
    for (int y1 = m; y1 >= 1; y1--) {
      for (int x2 = 1; x2 <= n; x2++) {
        for (int y2 = 1; y2 <= m; y2++) {
          ans[x1][y1][x2][y2] += ans[x1][y1 + 1][x2][y2];
        }
      }
    }
  }
  for (int x1 = n; x1 >= 1; x1--) {
    for (int y1 = m; y1 >= 1; y1--) {
      for (int x2 = 1; x2 <= n; x2++) {
        for (int y2 = 1; y2 <= m; y2++) {
          ans[x1][y1][x2][y2] += ans[x1][y1][x2 - 1][y2];
        }
      }
    }
  }
  for (int x1 = n; x1 >= 1; x1--) {
    for (int y1 = m; y1 >= 1; y1--) {
      for (int x2 = 1; x2 <= n; x2++) {
        for (int y2 = 1; y2 <= m; y2++) {
          ans[x1][y1][x2][y2] += ans[x1][y1][x2][y2 - 1];
        }
      }
    }
  }
  while (q--) {
    int x1, y1, x2, y2;
    std::cin >> x1 >> y1 >> x2 >> y2;
    std::cout << ans[x1][y1][x2][y2] << "\n";
  }
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve();
  return 0;
}