/**
 * @file    CF1520G To Go Or Not To Go?.cpp
 * @author  ForgotDream
 * @brief   BFS
 * @date    2023-09-02
 */
#include <cstring>
#include <iostream>
#include <queue>

using i64 = long long;
using pii = std::pair<int, int>;

constexpr int N = 2050;
constexpr int d[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int n, m, w;
int a[N][N];
bool vis[N][N];
i64 dis[N][N], f[2];
bool valid(int x, int y) { return 1 <= x && x <= n && 1 <= y && y <= m; }
void bfs(int sx, int sy, int k) {
  std::memset(dis, 0x3f, sizeof(dis));
  std::memset(vis, 0, sizeof(vis));
  vis[sx][sy] = true, dis[sx][sy] = 0, f[k] = 1e18;
  std::queue<pii> q;
  q.emplace(sx, sy);
  while (!q.empty()) {
    auto [x, y] = q.front();
    q.pop();
    if (a[x][y]) f[k] = std::min(f[k], dis[x][y] * w + a[x][y]);
    for (int i = 0; i < 4; i++) {
      int dx = x + d[i][0], dy = y + d[i][1];
      if (!valid(dx, dy) || a[dx][dy] == -1 || vis[dx][dy]) continue;
      dis[dx][dy] = dis[x][y] + 1, vis[dx][dy] = true;
      q.emplace(dx, dy);
    }
  }
}
void solve() {
  std::cin >> n >> m >> w;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) std::cin >> a[i][j];
  }
  bfs(1, 1, 0);
  bfs(n, m, 1);
  i64 ans = 1e18;
  if (vis[1][1]) ans = dis[1][1] * w;
  ans = std::min(ans, f[0] + f[1]);
  if (ans == 1e18) {
    std::cout << -1 << "\n";
    return;
  }
  std::cout << ans << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}