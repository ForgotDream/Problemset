/**
 * @file    LOJ#10072 Sightseeing Trip.cpp
 * @author  ForgotDream
 * @brief   SSSP
 * @date    2023-04-19
 */
#include <bits/stdc++.h>

using i64 = long long;
using i64u = unsigned long long;
using f80 = long double;

namespace MyFile {
  void useFileInuput() {
    #ifndef ONLINE_JUDGE
    freopen("tmp.in", "r", stdin);
    freopen("tmp.out", "w", stdout);
    #endif
    return;
  }
};

// template<std::queue<int> &path, const std::vector<std::vector<int>> &pre>
void findPath(int u, int v, std::queue<int> &path, const std::vector<std::vector<int>> &pre) {
  if (pre[u][v] == -1) {
    return;
  }

  findPath(u, pre[u][v], path, pre);
  path.push(pre[u][v]);
  findPath(pre[u][v], v, path, pre);

  return;
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<i64>> g(n, std::vector<i64>(n, INT_MAX));
  for (int i = 0; i < n; i++) {
    g[i][i] = 0;
  }
  for (int i = 0; i < m; i++) {
    int u, v, w;
    std::cin >> u >> v >> w;
    u--, v--;
    g[u][v] = g[v][u] = w;
  }

  auto dis = g;
  i64 ans = INT_MAX;
  static std::queue<int> path;
  static std::vector<std::vector<int>> pre(n, std::vector<int>(n, -1));

  for (int k = 0; k < n; k++) {
    for (int i = 0; i < k; i++) {
      for (int j = 0; j < i; j++) {
        if (ans > dis[i][j] + g[i][k] + g[k][j]) {
          ans = dis[i][j] + g[i][k] + g[k][j];
          while (!path.empty()) {
            path.pop();
          }
          path.push(i);
          findPath(i, j, path, pre);
          path.push(j), path.push(k);
        }
      }
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (dis[i][j] > dis[i][k] + dis[k][j]) {
          dis[i][j] = dis[i][k] + dis[k][j];
          pre[i][j] = k;
        }
      }
    }
  }

  if (ans == INT_MAX) {
    std::cout << "No solution." << "\n";
  } else {
    while (!path.empty()) {
      std::cout << path.front() + 1 << " ";
      path.pop();
    }
    std::cout << "\n";
  }

  return 0;
}