/**
 * @file    P6909 Keyboarding.cpp
 * @author  ForgotDream
 * @brief   BFS
 * @date    2023-04-02
 */
#include <bits/stdc++.h>

using i64 = long long;
using f80 = long double;

struct Node {
  int x, y, cur, t;
  Node(int x, int y, int c, int t) : x(x), y(y), cur(c), t(t) {}
};

signed main() {
  #ifndef ONLINE_JUDGE
  freopen("tmp.in", "r", stdin);
  freopen("tmp.out", "w", stdout);
  #endif

  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int r, c;
  std::cin >> r >> c;

  std::vector<std::string> a(r);
  for (int i = 0; i < r; i++) {
    std::cin >> a[i];
  }

  std::string s;
  std::cin >> s;
  s += "*";

  int len = s.length();

  std::vector<std::vector<std::vector<std::pair<int, int>>>> nxt(
    r, std::vector<std::vector<std::pair<int, int>>>(
      c, std::vector<std::pair<int, int>>(4)
    )
  );
  static const std::vector<std::vector<int>> d = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      for (int k = 0; k < 4; k++) {
        int dx = i + d[k][0], dy = j + d[k][1];
        while (dx >= 0 && dy >= 0 && dx < r && dy < c && a[dx][dy] == a[i][j]) {
          dx += d[k][0], dy += d[k][1];
        }
        if (dx < 0 || dy < 0 || dx >= r || dy >= c) {
          nxt[i][j][k] = std::make_pair(-1, -1);
        } else {
          nxt[i][j][k] = std::make_pair(dx, dy);
        }
      }
    }
  }

  std::queue<Node> q;

  std::vector<std::vector<int>> dis(r, std::vector<int>(c, -1e9));
  q.emplace(0, 0, -1, 0);
  while (!q.empty()) {
    auto cur = q.front();
    q.pop();

    if (a[cur.x][cur.y] == s[cur.cur + 1]) {
      q.emplace(cur.x, cur.y, cur.cur + 1, cur.t + 1);
      if (cur.cur + 1 == len - 1) {
        std::cout << cur.t + 1 << "\n";
        return 0;
      }
    } else {
      for (int i = 0; i < 4; i++) {
        if (nxt[cur.x][cur.y][i].first == -1) {
          continue;
        }
        int dx = nxt[cur.x][cur.y][i].first, dy = nxt[cur.x][cur.y][i].second;
        if (dis[dx][dy] < cur.cur) {
          dis[dx][dy] = cur.cur;
          q.emplace(dx, dy, cur.cur, cur.t + 1);
        }
      }
    }
  }

  return 0;
}