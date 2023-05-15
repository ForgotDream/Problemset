/**
 * @file    P2731 Riding the Fences.cpp
 * @author  ForgotDream
 * @brief   Euler Tour
 * @date    2023-05-15
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int n = 500;

struct Edge {
  int u, v, w;
  bool deleted;
  Edge(int _u, int _v, int _w) { u = _u, v = _v, w = _w, deleted = false; }
  void del() { deleted = true; }
};

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int m;
  std::cin >> m;

  std::vector<Edge> edges;
  std::vector<std::vector<int>> g(n);
  std::vector<int> deg(n);
  for (int i = 0; i < m; i++) {
    int u, v;
    std::cin >> u >> v;
    u--, v--;
    edges.emplace_back(u, v, 0);
    edges.emplace_back(v, u, 0);
    g[u].push_back(edges.size() - 2);
    g[v].push_back(edges.size() - 1);
    deg[u]++, deg[v]++;
  }

  for (int i = 0; i < n; i++) {
    std::sort(g[i].begin(), g[i].end(), [&](const int &lhs, const int &rhs) {
      return edges[lhs].v < edges[rhs].v;
    });
  }

  int s = 0;
  for (int i = 0; i < n; i++) {
    if (deg[i] & 1) {
      s = i;
      break;
    }
  }

  std::stack<int> ans;
  std::vector<int> cur(n);
  std::function<void(int)> dfs = [&](int u) {
    for (int &i = cur[u]; i < g[u].size();) {
      if (edges[g[u][i]].deleted) {
        i++;
      } else {
        int v = edges[g[u][i]].v;
        edges[g[u][i]].del(), edges[g[u][i] ^ 1].del();
        i++;
        dfs(v);
      }
    }
    ans.push(u);
  };

  dfs(s);

  while (!ans.empty()) {
    std::cout << ans.top() + 1 << "\n";
    ans.pop();
  }

  return 0;
}