/**
 * @file    LOJ#10105 欧拉回路.cpp
 * @author  ForgotDream
 * @brief   Euler Tour
 * @date    2023-05-15
 */
#include <bits/stdc++.h>

using i64 = long long;

struct Edge {
  int u, v;
  bool deleted;
  Edge(int _u, int _v) { u = _u, v = _v, deleted = false; }
  void del() { deleted = true; }
};

void directed() {
  int n, m;
  std::cin >> n >> m;

  std::vector<Edge> edges;
  std::vector<std::vector<int>> g(n); 
  std::vector<int> in(n), out(n);
  for (int i = 0; i < m; i++) {
    int u, v;
    std::cin >> u >> v;
    u--, v--;
    edges.emplace_back(u, v);
    g[u].push_back(edges.size() - 1);
    in[v]++, out[u]++;
  }

  int pivot = -1;
  for (int i = 0; i < n; i++) {
    if (in[i] != out[i]) {
      std::cout << "NO\n";
      return;
    }
  }

  for (int i = 0; i < n; i++) {
    if (in[i] || out[i]) {
      pivot = i;
      break;
    }
  }

  std::vector<int> cur(n);
  std::stack<int> ans;
  std::function<void(int)> dfs = [&](int u) {
    for (int &i = cur[u]; i < g[u].size();) {
      if (!edges[g[u][i]].deleted) {
        int v = edges[g[u][i]].v, pre = i;
        edges[g[u][i]].del();
        ++i;
        dfs(v);
        ans.push(g[u][pre]);
      } else {
        ++i;
      }
    }
  };

  dfs(pivot);

  if (ans.size() != m) {
    std::cout << "NO\n";
    return;
  }

  std::cout << "YES\n";
  while (!ans.empty()) {
    std::cout << ans.top() + 1 << " ";
    ans.pop();
  }
  std::cout << "\n";
}

void undirected() {
  int n, m;
  std::cin >> n >> m;

  std::vector<Edge> edges;
  std::vector<std::vector<int>> g(n); 
  std::vector<int> deg(n);
  for (int i = 0; i < m; i++) {
    int u, v;
    std::cin >> u >> v;
    u--, v--;
    edges.emplace_back(u, v);
    edges.emplace_back(v, u);
    g[u].push_back(edges.size() - 2);
    g[v].push_back(edges.size() - 1);
    deg[u]++, deg[v]++;
  }

  int pivot = -1;
  for (int i = 0; i < n; i++) {
    if (deg[i] % 2) {
      std::cout << "NO\n";
      return;
    }
  }

  for (int i = 0; i < n; i++) {
    if (!g[i].empty()) {
      pivot = i;
      break;
    }
  }

  std::vector<int> cur(n);
  std::stack<int> ans;
  std::function<void(int)> dfs = [&](int u) {
    for (int &i = cur[u]; i < g[u].size();) {
      if (!edges[g[u][i]].deleted) {
        int v = edges[g[u][i]].v, pre = i;
        edges[g[u][i]].del();
        edges[g[u][i] ^ 1].del();
        ++i;
        dfs(v);
        ans.push(((g[u][pre] >> 1) + 1) * ((g[u][pre] & 1) ? -1 : 1));
      } else {
        ++i;
      }
    }
  };

  dfs(pivot);

  if (ans.size() != m) {
    std::cout << "NO\n";
    return;
  }

  std::cout << "YES\n";
  while (!ans.empty()) {
    std::cout << ans.top() << " ";
    ans.pop();
  }
  std::cout << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  std::cin >> t;

  if (t == 1) {
    undirected();
  } else {
    directed();
  }

  return 0;
}