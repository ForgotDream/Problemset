/**
 * @file    CF1033A King Escape.cpp
 * @author  ForgotDream
 * @brief   BFS
 * @date    2023-08-29
 */
#include <cmath>
#include <iostream>
#include <queue>

using i64 = long long;
using pii = std::pair<int, int>;

constexpr int N = 1050;
constexpr int d[][2] = {{1, 0}, {-1, 0}, {0, 1},  {0, -1},
                        {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
bool vis[N][N];
int n;
int ax, ay, bx, by, cx, cy;
bool valid(int x, int y) {
  if (x < 1 || x > n || y < 1 || y > n) return false;
  if (x == ax || y == ay) return false;
  if (x + y == ax + ay || x - y == ax - ay) return false;
  return true;
}
void solve() {
  std::cin >> n;
  std::cin >> ax >> ay >> bx >> by >> cx >> cy;
  std::queue<pii> q;
  if (!valid(bx, by)) {
    std::cout << "NO\n";
    return;
  }
  q.emplace(bx, by);
  vis[bx][by] = true;
  while (!q.empty()) {
    auto [x, y] = q.front();
    q.pop();
    for (int i = 0; i < 8; i++) {
      int dx = x + d[i][0], dy = y + d[i][1];
      if (!valid(dx, dy) || vis[dx][dy]) continue;
      if (dx == cx && dy == cy) {
        std::cout << "YES\n";
        return;
      }
      q.emplace(dx, dy);
      vis[dx][dy] = true;
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