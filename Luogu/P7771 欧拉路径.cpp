/**
 * @file    P7771 欧拉路径.cpp
 * @author  ForgotDream
 * @brief   Euler Tour
 * @date    2023-05-10
 */
#include <bits/stdc++.h>

using i64 = long long;

struct Edge {
  int u, v, w;
  bool deleted;
  Edge(int _u, int _v, int _w) : u(_u), v(_v), w(_w) { deleted = false; }
  void del() { deleted = true; }
};

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int n, m;
  std::cin >> n >> m;

  std::vector<Edge> edges;
  std::vector<std::vector<int>> g(n + 1);
  std::vector<int> in(n + 1), out(n + 1);
  for (int i = 0; i < m; i++) {
    int u, v;
    std::cin >> u >> v;
    edges.emplace_back(u, v, 0);
    g[u].push_back(edges.size() - 1);
    out[u]++, in[v]++;
  }
  
  for (int i = 1; i <= n; i++) {
    if (g[i].empty()) {
      continue;
    }
    std::sort(g[i].begin(), g[i].end(), [&](const int &lhs, const int &rhs) {
      return edges[lhs].v < edges[rhs].v;
    });
  }

  int pivot = 1;
  std::array<int, 2> p = {0, 0};
  bool flg = true;
  for (int i = 1; i <= n; i++) {
    if (in[i] != out[i]) {
      flg = false;
      if (out[i] - in[i] == 1) {
        p[0]++;
        pivot = i;
      } else if (in[i] - out[i] == 1) {
        p[1]++;
      } else {
        std::cout << "No\n";
        return 0;
      }
    }
  }

  if (!flg && !(p[0] == p[1] && p[1] == 1)) {
    std::cout << "No\n";
    return 0;
  }

  std::stack<int> ans;
  std::vector<int> cnt(n + 1);
  std::function<void(int)> dfs = [&](int u) {
    for (int &i = cnt[u]; i < g[u].size();) {
      if (!edges[g[u][i]].deleted) {
        edges[g[u][i]].del();
        int v = edges[g[u][i]].v;
        i++;
        dfs(v);
      } else {
        i++;
      }
    }
    ans.push(u);
    return;
  };

  dfs(pivot);

  if (ans.empty()) {
    std::cout << "No\n";
  } else {
    while (!ans.empty()) {
      std::cout << ans.top() << " ";
      ans.pop();
    }
    std::cout << "\n";
  }

  return 0;
}