/**
 * @file    CF1613E Crazy Robot.cpp
 * @author  ForgotDream
 * @brief   BFS
 * @date    2023-08-22
 */
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using i64 = long long;
using pii = std::pair<int, int>;

constexpr int d[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

int n, m;
std::vector<std::vector<bool>> vis;
std::vector<std::vector<char>> a;
int sx, sy;
bool valid(int x, int y) { return 1 <= x && x <= n && 1 <= y && y <= m; }
int calc(int x, int y) {
  int res = 0;
  for (int i = 0; i < 4; i++) {
    int dx = x + d[i][0], dy = y + d[i][1];
    if (valid(dx, dy)) res += a[dx][dy] == '.';
  }
  return res;
}
void solve() {
  std::cin >> n >> m;
  a.clear(), a.resize(n + 1, std::vector<char>(m + 1));
  vis.clear(), vis.resize(n + 1, std::vector<bool>(m + 1));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      std::cin >> a[i][j];
      if (a[i][j] == 'L') sx = i, sy = j;
    }
  }
  std::queue<pii> q;
  q.emplace(sx, sy), vis[sx][sy] = true;
  while (!q.empty()) {
    auto u = q.front();
    auto [x, y] = u;
    q.pop();
    for (int i = 0; i < 4; i++) {
      int dx = x + d[i][0], dy = y + d[i][1];
      if (!valid(dx, dy) || vis[dx][dy] || a[dx][dy] == '#' ||
          calc(dx, dy) >= 2) {
        continue;
      }
      vis[dx][dy] = true, a[dx][dy] = '+', q.emplace(dx, dy);
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      std::cout << a[i][j];
    }
    std::cout << "\n";
  }
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t;
  std::cin >> t;
  while (t--) solve();
  return 0;
}