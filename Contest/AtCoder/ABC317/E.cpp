#include <algorithm>
#include <iostream>
#include <queue>

using i64 = long long;
using pii = std::pair<int, int>;

constexpr int N = 2050;
constexpr int d[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int h, w, dis[N][N];
char a[N][N];
bool f[4][N][N], g[N][N];
int sx, sy, tx, ty;
bool valid(int x, int y) { return 1 <= x && x <= h && 1 <= y && y <= w; }
void solve() {
  std::cin >> h >> w;
  for (int i = 1; i <= h; i++) {
    for (int j = 1; j <= w; j++) std::cin >> a[i][j];
  }
  for (int i = 1; i <= h; i++) {
    for (int j = 1; j <= w; j++) {
      char cur = a[i][j];
      if (cur == 'S') sx = i, sy = j;
      if (cur == 'G') tx = i, ty = j;
      if (cur == '>') f[0][i][j] = true;
      else if (cur == '.' || cur == 'S' || cur == 'G') f[0][i][j] = f[0][i][j - 1];
      if (cur == 'v') f[2][i][j] = true;
      else if (cur == '.' || cur == 'S' || cur == 'G') f[2][i][j] = f[2][i - 1][j];
    }
  }
  for (int i = h; i >= 1; i--) {
    for (int j = w; j >= 1; j--) {
      char cur = a[i][j];
      if (cur == '<') f[1][i][j] = true;
      else if (cur == '.' || cur == 'S' || cur == 'G') f[1][i][j] = f[1][i][j + 1];
      if (cur == '^') f[3][i][j] = true;
      else if (cur == '.' || cur == 'S' || cur == 'G') f[3][i][j] = f[3][i + 1][j];
    }
  }
  for (int i = 1; i <= h; i++) {
    for (int j = 1; j <= w; j++) {
      bool cur = false;
      for (int k = 0; k < 4; k++) cur |= f[k][i][j];
      g[i][j] = cur;
    }
  }
  std::queue<pii> q;
  q.emplace(sx, sy), dis[sx][sy] = 1;
  while (!q.empty()) {
    auto [x, y] = q.front();
    q.pop();
    for (int i = 0; i < 4; i++) {
      int dx = x + d[i][0], dy = y + d[i][1];
      if (!valid(dx, dy) || a[dx][dy] == '#' || g[dx][dy]) continue;
      if (dis[dx][dy]) continue;
      dis[dx][dy] = dis[x][y] + 1;
      if (dx == tx && dy == ty) {
        std::cout << dis[dx][dy] - 1 << "\n";
        return;
      }
      q.emplace(dx, dy);
    }
  }
  std::cout << -1 << "\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}