/**
 * @file    CF253C Text Editor.cpp
 * @author  ForgotDream
 * @brief   BFS
 * @date    2023-08-25
 */
#include <algorithm>
#include <iostream>
#include <queue>

using i64 = long long;
using pii = std::pair<int, int>;

constexpr int N = 105, M = 1e5 + 50;
constexpr int d[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int n, a[N], x1, y1, x2, y2;
int dis[N][M];
bool valid(int x, int y) { return 1 <= x && x <= n && 1 <= y && y <= a[x] + 1; }
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  std::cin >> x1 >> y1 >> x2 >> y2;
  if (x1 == x2 && y1 == y2) {
    std::cout << 0 << "\n";
    return;
  }
  std::queue<pii> q;
  q.emplace(x1, y1);
  dis[x1][y1] = 1;
  while (!q.empty()) {
    auto [x, y] = q.front();
    q.pop();
    for (int i = 0; i < 4; i++) {
      int dx = x + d[i][0], dy = std::min(y + d[i][1], a[x + d[i][0]] + 1);
      if (!valid(dx, dy) || dis[dx][dy]) continue;
      dis[dx][dy] = dis[x][y] + 1;
      if (dx == x2 && dy == y2) {
        std::cout << dis[dx][dy] - 1 << "\n";
        return;
      }
      q.emplace(dx, dy);
    }
  }
}

signed main() {
  std::freopen("input.txt", "r", stdin);
  std::freopen("output.txt", "w", stdout);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}