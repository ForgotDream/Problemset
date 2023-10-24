/**
 * @file    LOJ#10028 Knight Moves.cpp
 * @author  ForgotDream
 * @brief   BFS
 * @date    2023-03-29
 */
#include <bits/stdc++.h>

using i64 = long long;
using f80 = long double;

void solve() {
  static const std::vector<std::vector<int>> d = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, 
                                                  {1, 2}, {1, -2}, {2, 1}, {2, -1}};

  int sx, sy, ex, ey, l;
  std::cin >> l >> sx >> sy >> ex >> ey;

  if (sx == ex && sy == ey) {
    std::cout << 0 << "\n";
    return;
  }

  std::queue<std::pair<int, int>> q;
  std::vector<std::vector<int>> dis(l, std::vector<int>(l, 1e9));

  q.emplace(sx, sy);
  dis[sx][sy] = 0;
  while (!q.empty()) {
    int x = q.front().first, y= q.front().second;
    q.pop();
    for (int i = 0; i < 8; i++) {
      int dx = x + d[i][0], dy = y + d[i][1];
      
      if (dx < 0 || dy < 0 || dx >= l || dy >= l) {
        continue;
      } else if (dis[dx][dy] != 1e9) {
        continue;
      }

      dis[dx][dy] = dis[x][y] + 1;

      if (dx == ex && dy == ey) {
        std::cout << dis[dx][dy] << "\n";
        return;
      }

      q.emplace(dx, dy);
    }
  }

  return;
}

signed main() {
  #ifndef ONLINE_JUDGE
  freopen("tmp.in", "r", stdin);
  freopen("tmp.out", "w", stdout);
  #endif

  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int t;
  std::cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}