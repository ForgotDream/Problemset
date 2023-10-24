#include <bits/stdc++.h>

using i64 = long long;

constexpr int d[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

void solve() {
  int n, m;
  std::cin >> n >> m;

  std::vector a(n, std::vector<int>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      std::cin >> a[i][j];
    }
  }

  auto valid = [&](int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
  };

  std::vector vis(n, std::vector<bool>(m));

  auto bfs = [&](int sx, int sy) -> int {
    std::queue<std::pair<int, int>> q;
    int res = 0;

    q.emplace(sx, sy);
    vis[sx][sy] = true;
    while (!q.empty()) {
      int x = q.front().first, y = q.front().second;
      res += a[x][y];
      q.pop();
      for (int i = 0; i < 4; i++) {
        int dx = x + d[i][0], dy = y + d[i][1];
        if (valid(dx, dy) && !vis[dx][dy] && a[dx][dy] != 0) {
          vis[dx][dy] = true;
          q.emplace(dx, dy);
        }
      }
    }

    return res;
  };

  int ans = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (!vis[i][j] && a[i][j] != 0) {
        ans = std::max(bfs(i, j), ans);
      }
    }
  }

  std::cout << ans << "\n";

  return;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int t;
  std::cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}