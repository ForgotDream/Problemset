/**
 * @file    CF275B Convex Shape.cpp
 * @author  ForgotDream
 * @brief   shabi
 * @date    2023-09-02
 */
#include <cmath>
#include <iostream>
#include <queue>

using i64 = long long;
using pii = std::pair<int, int>;

constexpr int N = 55;
int n, m;
char a[N][N];
int s1[N][N], s2[N][N];
int sum1(int x1, int x2, int y) {
  if (x1 > x2) std::swap(x1, x2);
  return s1[x2][y] - s1[x1 - 1][y];
}
int sum2(int y1, int y2, int x) {
  if (y1 > y2) std::swap(y1, y2);
  return s2[x][y2] - s2[x][y1 - 1];
}
void solve() {
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) std::cin >> (a[i] + 1);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      s1[i][j] = s1[i - 1][j] + (a[i][j] == 'B');
      s2[i][j] = s2[i][j - 1] + (a[i][j] == 'B');
    }
  }
  for (int x1 = 1; x1 <= n; x1++) {
    for (int y1 = 1; y1 <= m; y1++) {
      for (int x2 = 1; x2 <= n; x2++) {
        for (int y2 = 1; y2 <= m; y2++) {
          if (a[x1][y1] != 'B' || a[x2][y2] != 'B') continue;
          bool flg = false;
          int d = std::abs(x2 - x1) + std::abs(y2 - y1) + 1;
          if (sum1(x1, x2, y1) + sum2(y1, y2, x2) == d + 1) flg = true;
          if (sum1(x1, x2, y2) + sum2(y1, y2, x1) == d + 1) flg = true;
          if (!flg) {
            std::cout << "NO\n";
            return;
          }
        }
      }
    }
  }
  std::cout << "YES\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}