/**
 * @file    CF389B Fox and Cross.cpp
 * @author  ForgotDream
 * @brief   shabi
 * @date    2023-09-02
 */
#include <algorithm>
#include <cmath>
#include <iostream>

using i64 = long long;

constexpr int N = 105;
constexpr int d[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int n;
char a[N][N];
bool used[N][N];
bool valid(int x, int y) { return 1 <= x && x <= n && 1 <= y && y <= n; }
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> (a[i] + 1);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (used[i][j] || a[i][j] == '.') continue;
      bool flg = true;
      for (int k = 0; k < 4; k++) {
        int dx = i + d[k][0], dy = j + d[k][1];
        if (!valid(dx, dy) || a[dx][dy] == '.' || used[dx][dy]) {
          flg = false;
          break;
        }
      }
      if (!flg) continue;
      used[i][j] = true;
      for (int k = 0; k < 4; k++) {
        int dx = i + d[k][0], dy = j + d[k][1];
        used[dx][dy] = true;
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (a[i][j] == '#' && !used[i][j]) {
        std::cout << "NO\n";
        return;
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