#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;
using status = std::tuple<int, int, int, int>;

constexpr int N = 65;
constexpr int d[][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int n;
bool a[N][N];
int dis[N][N][N][N];

void solve() {
  std::cin >> n;

  int sx[2], sy[2], p = 0;
  for (int i = 1; i <= n; i++) {
    char c;
    for (int j = 1; j <= n; j++) {
      std::cin >> c;
      if (c == 'P') sx[p] = i, sy[p++] = j;
      else if (c == '#') a[i][j] = true;
    }
  }

  std::queue<status> q;
  q.emplace(sx[0], sy[0], sx[1], sy[1]), dis[sx[0]][sy[0]][sx[1]][sy[1]] = 1;
  while (!q.empty()) {
    auto [x1, y1, x2, y2] = q.front();
    q.pop();
    for (auto [dx, dy] : d) {
      int x3 = x1 + dx, y3 = y1 + dy;
      int x4 = x2 + dx, y4 = y2 + dy;

      if (x3 < 1) x3 = 1;
      else if (x3 > n) x3 = n;
      else if (a[x3][y3]) x3 = x1, y3 = y1;
      if (y3 < 1) y3 = 1;
      else if (y3 > n) y3 = n;
      else if (a[x3][y3]) x3 = x1, y3 = y1;

      if (x4 < 1) x4 = 1;
      else if (x4 > n) x4 = n;
      else if (a[x4][y4]) x4 = x2, y4 = y2;
      if (y4 < 1) y4 = 1;
      else if (y4 > n) y4 = n;
      else if (a[x4][y4]) x4 = x2, y4 = y2;

      if (dis[x3][y3][x4][y4]) continue;
      if (x3 == x4 && y3 == y4) {
        std::cout << dis[x1][y1][x2][y2] << "\n";
        return;
      }

      q.emplace(x3, y3, x4, y4);
      dis[x3][y3][x4][y4] = dis[x1][y1][x2][y2] + 1;
    }
  }

  std::cout << -1 << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
