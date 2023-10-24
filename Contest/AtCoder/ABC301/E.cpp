#include <bits/stdc++.h>

using i64 = long long;

constexpr int d[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
constexpr int inf = 1e9;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);


  int n, m, t;
  std::cin >> n >> m >> t;

  int sx, sy, tx, ty, cnt = 0;
  std::vector a(n + 1, std::vector<char>(m + 1));
  std::vector<std::pair<int, int>> p;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      std::cin >> a[i][j];
      if (a[i][j] == 'S') {
        sx = i, sy = j;
      } else if (a[i][j] == 'G') {
        tx = i, ty = j;
      } else if (a[i][j] == 'O') {
        p.emplace_back(i, j);
        cnt++;
      }
    }
  }

  auto valid = [&](int i, int j) {
    return i >= 1 && i <= n && j >= 1 && j <= m && a[i][j] != '#';
  };

  std::queue<std::pair<int, int>> q;
  std::vector vis(n + 1, std::vector<bool>(m + 1));
  std::vector dis(n + 1, std::vector(m + 1, std::vector<int>(p.size() + 1, inf)));
  vis[sx][sy] = true, dis[sx][sy][0] = 0;
  q.emplace(sx, sy);
  while (!q.empty()) {
    int x = q.front().first, y = q.front().second;
    q.pop();
    for (int i = 0; i < 4; i++) {
      int dx = x + d[i][0], dy = y + d[i][1];
      if (!valid(dx, dy) || vis[dx][dy]) {
        continue;
      }
      dis[dx][dy][0] = dis[x][y][0] + 1;
      vis[dx][dy] = true;
      if (dx == tx && dy == ty) {
        continue;
      }
      q.emplace(dx, dy);
    }
  }

  for (int k = 0; k < p.size(); k++) {
    int sx = p[k].first, sy = p[k].second;
    std::queue<std::pair<int, int>> q;
    std::vector vis(n + 1, std::vector<bool>(m + 1)); 
    vis[sx][sy] = true, dis[sx][sy][k + 1] = 0;
    q.emplace(sx, sy);
    while (!q.empty()) {
      int x = q.front().first, y = q.front().second;
      q.pop();
      for (int i = 0; i < 4; i++) {
        int dx = x + d[i][0], dy = y + d[i][1];
        if (!valid(dx, dy) || vis[dx][dy]) {
          continue;
        }
        dis[dx][dy][k + 1] = dis[x][y][k + 1] + 1;
        vis[dx][dy] = true;
        if (dx == tx && dy == ty) {
          continue;
        }
        q.emplace(dx, dy);
      }
    }
  }

  int ans = 0;
  std::function<void(int, int, int)> dfs = [&](int idx, int cur, int st) {
    if (cur > t) {
      return;
    }
    if (st == (1 << p.size()) - 1) {
      ans = std::max(ans, cur + dis[idx + 1][tx][ty]);
      return;
    }
    for (int i = 0; i < p.size(); i++) {
      if (!(st & (1 << i))) {
        int x = p[i].first, y = p[i].second;
        dfs(i, cur + dis[idx + 1][x][y], st | (1 << i));
      }
    }
  };

  dfs(0, 0, 0);

  std::cout << ans << "\n";

  return 0;
}