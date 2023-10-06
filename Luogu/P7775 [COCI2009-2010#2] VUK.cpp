/**
 * @file    P7775 [COCI2009-2010#2] VUK.cpp
 * @author  ForgotDream
 * @brief   BFS
 * @date    2023-10-04
 */
#include <iostream>
#include <queue>
#include <tuple>

using i64 = long long;
using pii = std::pair<int, int>;
using ti3 = std::tuple<int, int, int>;

constexpr int N = 550;
constexpr int d[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int n, m;
int sx, sy, tx, ty;
bool a[N][N], vis[N][N];
int dis[N][N];
bool valid(int x, int y) { return 1 <= x && x <= n && 1 <= y && y <= m; }
void solve() {
  std::cin >> n >> m;
  std::queue<pii> q;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      char c;
      std::cin >> c;
      if (c == 'V') sx = i, sy = j;
      if (c == 'J') tx = i, ty = j;
      if (c == '+') a[i][j] = true, q.emplace(i, j);
    }
  }
  while (!q.empty()) {
    auto [x, y] = q.front();
    q.pop();
    for (int i = 0; i < 4; i++) {
      int dx = x + d[i][0], dy = y + d[i][1];
      if (!valid(dx, dy) || a[dx][dy] || dis[dx][dy]) continue;
      dis[dx][dy] = dis[x][y] + 1;
      q.emplace(dx, dy);
    }
  }
  std::cout << [&]() {
    std::priority_queue<ti3> q;
    q.emplace(dis[sx][sy], sx, sy), vis[sx][sy] = true;
    while (!q.empty()) {
      auto [di, x, y] = q.top();
      q.pop();
      for (int i = 0; i < 4; i++) {
        int dx = x + d[i][0], dy = y + d[i][1];
        if (!valid(dx, dy) || vis[dx][dy]) continue;
        vis[dx][dy] = true;
        q.emplace(std::min(di, dis[dx][dy]), dx, dy);
        if (dx == tx && dy == ty) return std::min(di, dis[dx][dy]);
      }
    }
    return -1;
  }() << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
