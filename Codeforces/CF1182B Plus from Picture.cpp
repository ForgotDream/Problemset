/**
 * @file    CF1182B Plus from Picture.cpp
 * @author  ForgotDream
 * @brief   shabi
 * @date    2023-08-29
 */
#include <iostream>

using i64 = long long;

constexpr int N = 550;
constexpr int d[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int h, w, all;
bool a[N][N];
bool valid(int x, int y) { return 1 <= x && x <= h && 1 <= y && y <= w; }
bool check(int x, int y) {
  int cnt = 1;
  for (int i = 0; i < 4; i++) {
    int dx = x + d[i][0], dy = y + d[i][1];
    if (!valid(dx, dy) || !a[dx][dy]) return false;
    while (valid(dx, dy) && a[dx][dy]) cnt++, dx += d[i][0], dy += d[i][1];
  }
  return cnt == all;
}
void solve() {
  std::cin >> h >> w;
  for (int i = 1; i <= h; i++) {
    for (int j = 1; j <= w; j++) {
      char c;
      std::cin >> c;
      a[i][j] = (c == '*');
      all += a[i][j];
    }
  }
  for (int i = 1; i <= h; i++) {
    for (int j = 1; j <= w; j++) {
      if (a[i][j] && check(i, j)) {
        std::cout << "YES\n";
        return;
      }
    }
  }
  std::cout << "NO\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}