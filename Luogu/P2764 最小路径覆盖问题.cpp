/**
 * @file    P2764 最小路径覆盖问题.cpp
 * @author  ForgotDream
 * @brief   最大流
 * @date    2023-08-17
 */
#include <iostream>
#include <numeric>
#include <vector>
#include <cstring>
#include <queue>

using i64 = long long;

int n, m;

#pragma region
template<int N = 1050>
struct Dinic {
  struct Edge {
    int u, v;
    i64 cap, flow;
    Edge(int _u = 0, int _v = 0, i64 _c = 0) {
      u = _u, v = _v, cap = _c, flow = 0;
    }
  };
  int s, t;
  std::vector<Edge> edges;
  std::vector<int> adj[N];
  int dis[N], cur[N];
  Dinic() = default;
  void addEdge(int u, int v, i64 cap) {
    edges.emplace_back(u, v, cap);
    edges.emplace_back(v, u, 0);
    adj[u].push_back(edges.size() - 2);
    adj[v].push_back(edges.size() - 1);
  }
  bool bfs() {
    std::memset(dis, 0, sizeof(dis));
    std::memset(cur, 0, sizeof(cur));
    std::queue<int> q;
    q.push(s), dis[s] = 1;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (auto i : adj[u]) {
        auto [_, v, cap, flow] = edges[i];
        if (!dis[v] && cap > flow) dis[v] = dis[u] + 1, q.push(v);
      }
    }
    return dis[t];
  }
  i64 dfs(int u, i64 lim) {
    if (u == t || !lim) return lim;
    i64 res = 0;
    for (int &i = cur[u]; i < adj[u].size(); i++) {
      auto &[_, v, cap, flow] = edges[adj[u][i]];
      i64 f;
      if (dis[v] == dis[u] + 1 && (f = dfs(v, std::min(lim, cap - flow))) > 0) {
        flow += f, edges[adj[u][i] ^ 1].flow -= f;
        res += f, lim -= f;
        if (!lim) break;
      }
    }
    return res;
  }
  i64 maxFlow(int s, int t) {
    this->s = s, this->t = t;
    i64 res = 0;
    while (bfs()) res += dfs(s, 1e9);
    return res;
  }
};
Dinic solver;
#pragma endregion

#pragma region
template<int N = 1050>
struct DSU {
  int fa[N];
  DSU() { std::iota(fa, fa + N, 0); }
  int find(int u) { return u == fa[u] ? u : fa[u] = find(fa[u]); }
  bool merge(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return false;
    fa[u] = v;
    return true;
  }
};
DSU dsu;
#pragma endregion

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n >> m;
  int s = 0, t = 2 * n + 1;

  for (int i = 1; i <= n; i++) {
    solver.addEdge(s, i, 1);
    solver.addEdge(n + i, t, 1);
  }
  for (int i = 1, u, v; i <= m; i++) {
    std::cin >> u >> v;
    solver.addEdge(u, v + n, 1);
  }
  
  int ans = n - solver.maxFlow(s, t);

  for (int u = 1; u <= n; u++) {
    for (auto i : solver.adj[u]) {
      auto [_, v, cap, flow] = solver.edges[i];
      if (cap == flow && v != s) dsu.merge(u, v - n);
    }
  }

  for (int i = n; i >= 1; i--) {
    bool flg = false;
    for (int j = 1; j <= n; j++) {
      if (dsu.find(j) == i) std::cout << j << " ", flg = true;
    }
    if (flg) std::cout << "\n";
  }
  std::cout << ans << "\n";

  return 0;
}