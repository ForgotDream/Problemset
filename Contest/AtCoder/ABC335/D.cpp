#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 50;
constexpr int d[][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
int n;
bool vis[N][N];
int ans[N][N];

bool valid(int x, int y) {
  return 1 <= x && x <= n && 1 <= y && y <= n && !vis[x][y];
}

void solve() {
  std::cin >> n;
  int cnt = n * n - 1, p = 0, sx = 1, sy = 1;
  for (int i = 1; i <= cnt; i++) {
    ans[sx][sy] = i, vis[sx][sy] = true;
    int dx = sx + d[p][0], dy = sy + d[p][1];
    if (!valid(dx, dy)) p = (p + 1) % 4;
    dx = sx + d[p][0], dy = sy + d[p][1];
    sx = dx, sy = dy;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (!ans[i][j]) {
        std::cout << "T ";
        continue;
      }
      std::cout << ans[i][j] << " \n"[j == n];
    }
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
