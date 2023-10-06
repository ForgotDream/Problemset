/**
 * @file    P2937 [USACO09JAN] Laserphones S.cpp
 * @author  ForgotDream
 * @brief   01 BFS
 * @date    2023-10-04
 */
#include <cstring>
#include <iostream>
#include <deque>
#include <tuple>
#include <vector>

using i64 = long long;
using pii = std::pair<int, int>;
using ti3 = std::tuple<int, int, int>;

constexpr int N = 105;
constexpr int d[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
std::deque<ti3> dq;
int h, w;
std::vector<pii> s;
bool a[N][N];
int dis[N][N][4];
bool valid(int x, int y) { return 1 <= x && x <= h && 1 <= y && y <= w; }
void solve() {
  std::cin >> w >> h;
  for (int i = 1; i <= h; i++) {
    for (int j = 1; j <= w; j++) {
      char c;
      std::cin >> c;
      if (c == 'C') s.emplace_back(i, j); 
      if (c == '*') a[i][j] = true;
    }
  }
  std::memset(dis, 0x3f, sizeof(dis));
  auto [sx, sy] = s[0];
  for (int i = 0; i < 4; i++) {
    int dx = sx + d[i][0], dy = sy + d[i][1];
    if (!valid(dx, dy) || a[dx][dy]) continue;
    dq.emplace_back(dx, dy, i), dis[dx][dy][i] = 0;
  }
  while (!dq.empty()) {
    auto [x, y, to] = dq.front();
    dq.pop_front();
    for (int i = 0; i < 4; i++) {
      if ((i ^ 1) == to) continue;
      int dx = x + d[i][0], dy = y + d[i][1];
      if (!valid(dx, dy) || a[dx][dy]) continue;
      if (dis[dx][dy][i] > dis[x][y][to] + (i != to)) {
        dis[dx][dy][i] = dis[x][y][to];
        if (i == to) dq.emplace_front(dx, dy, i);
        else dis[dx][dy][i]++, dq.emplace_back(dx, dy, i);
      }
    }
  }
  int ans = 1e9;
  auto [tx, ty] = s[1];
  for (int i = 0; i < 4; i++) {
    if (dis[tx][ty][i] == 0x3f3f3f3f) continue;
    ans = std::min(ans, dis[tx][ty][i]);
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
