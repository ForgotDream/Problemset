/**
 * @file    CF377A Maze.cpp
 * @author  ForgotDream
 * @brief   BFS
 * @date    2023-09-05
 */
#include <iostream>
#include <queue>

using i64 = long long;
using pii = std::pair<int, int>;

constexpr int N = 550;
constexpr int d[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int n, m, k;
char a[N][N];
bool valid(int x, int y) { return 1 <= x && x <= n && 1 <= y && y <= m; }
void solve() {
  std::cin >> n >> m >> k;
  for (int i = 1; i <= n; i++) std::cin >> (a[i] + 1);
  std::queue<pii> q;
  int cnt = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (a[i][j] == '.') {
        a[i][j] = 'X';
        if (q.empty()) q.emplace(i, j), ++k, a[i][j] = '.';
        cnt++;
      }
    }
  }
  if (k == cnt) goto output;
  while (!q.empty()) {
    auto [x, y] = q.front();
    q.pop();
    for (int i = 0; i < 4; i++) {
      int dx = x + d[i][0], dy = y + d[i][1];
      if (!valid(dx, dy) || a[dx][dy] != 'X') continue;
      q.emplace(dx, dy);
      a[dx][dy] = '.';
      if (++k == cnt) goto output;
    }
  }
  output: for (int i = 1; i <= n; i++) std::cout << a[i] + 1 << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}