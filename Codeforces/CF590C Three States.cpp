/**
 * @file    CF590C Three States.cpp
 * @author  ForgotDream
 * @brief   BFS
 * @date    2023-08-26
 */
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

constexpr int N = 1e3 + 5, inf = 1e9;
constexpr int d[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int n, m;
char a[N][N];
std::vector<std::pair<int, int> > ct[4];
int dis[4][N][N];
bool valid(int x, int y) { return 1 <= x && x <= n && 1 <= y && y <= m; }
void bfs(int t) {
  std::queue<std::pair<int, int> > q;
  for (auto i : ct[t]) {
    q.push(i);
    dis[t][i.first][i.second] = 0;
  }
  while (!q.empty()) {
    auto [x, y] = q.front();
    q.pop();
    for (int i = 0; i < 4; i++) {
      int dx = x + d[i][0], dy = y + d[i][1];
      if (!valid(dx, dy)) continue;
      if (dis[t][dx][dy] != 1e8 || a[dx][dy] == '#') continue;
      dis[t][dx][dy] = dis[t][x][y] + 1;
      q.emplace(dx, dy);
    }
  }
}
void solve() {
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) {
      std::cin >> a[i][j];
      dis[1][i][j] = dis[2][i][j] = dis[3][i][j] = 1e8;
      if (std::isdigit(a[i][j])) ct[a[i][j] - '0'].emplace_back(i, j);
    }
  bfs(1);
  bfs(2);
  bfs(3);
  int ans = inf, dis12 = inf, dis23 = inf, dis13 = inf;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      ans = std::min(ans, dis[1][i][j] + dis[2][i][j] + dis[3][i][j] - 2);
      dis12 = std::min(dis12, dis[1][i][j] + dis[2][i][j] - 1);
      dis23 = std::min(dis23, dis[2][i][j] + dis[3][i][j] - 1);
      dis13 = std::min(dis13, dis[1][i][j] + dis[3][i][j] - 1);
    }
  }
  ans = std::min({ans, dis12 + dis13, dis12 + dis23, dis13 + dis23});
  if (ans > 1e7) std::cout << -1 << "\n";
  else std::cout << ans << "\n";
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}