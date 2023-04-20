/**
 * @file    P3456 GRZ-Ridges and Valleys.cpp
 * @author  ForgotDream
 * @brief   BFS
 * @date    2023-04-02
 */
#include <bits/stdc++.h>

using i64 = long long;
using f80 = long double;

int ans1, ans2;
std::vector<std::vector<bool>> vis;
std::vector<std::vector<int>> a;
void bfs(int sx, int sy) {
  static const std::vector<std::vector<int>> d = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}, 
                                                  {1, 1}, {-1, 1}, {1, -1}, {-1, -1}};
  int n = a.size();
  std::queue<std::pair<int, int>> q;
  bool peak = false, valley = false;

  q.emplace(sx, sy);
  vis[sx][sy] = true;
  while (!q.empty()) {
    int x = q.front().first, y = q.front().second;
    q.pop();
    for (int i = 0; i < 8; i++) {
      int dx = x + d[i][0], dy = y + d[i][1];
      if (dx < 0 || dy < 0 || dx >= n || dy >= n) {
        continue;
      }

      if (a[dx][dy] < a[x][y]) {
        peak = true;
      } else if (a[dx][dy] > a[x][y]) {
        valley = true;
      } else {
        if (vis[dx][dy]) {
          continue;
        }
        q.emplace(dx, dy);
        vis[dx][dy] = true;
      }
    }
  }

  if (peak && !valley) {
    ans1++;
  } else if (valley && !peak) {
    ans2++;
  }

  return;
}

signed main() {
  #ifndef ONLINE_JUDGE
  freopen("tmp.in", "r", stdin);
  freopen("tmp.out", "w", stdout);
  #endif

  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  vis.resize(n, std::vector<bool>(n));
  a.resize(n, std::vector<int>(n));

  bool same = true;
  int cur;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      std::cin >> a[i][j];
      if (i == 0 && j == 0) {
        cur = a[i][j];
      } else if (cur != a[i][j]) {
        same = false;
      }
    }
  }

  if (same) {
    std::cout << 1 << " " << 1 << "\n";
    return 0;
  }

  std::queue<std::pair<int, int>> q;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (!vis[i][j]) {
        bfs(i, j);
      }
    }
  }

  std::cout << ans1 << " " << ans2 << "\n";

  return 0;
}