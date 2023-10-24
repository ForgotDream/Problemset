/**
 * @file    P1402 酒店之王.cpp
 * @author  ForgotDream
 * @brief   最大流
 * @date    2023-08-17
 */
#include <iostream>
#include <vector>
#include <cstring>
#include <queue>

using i64 = long long;

int n, p, q;

#pragma region
template<int N = 100050>
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

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n >> p >> q;
  int s = 0, t = p + q + 2 * n + 1;
  for (int i = 1; i <= n; i++) solver.addEdge(p + i, p + n + i, 1);
  for (int i = 1; i <= p; i++) solver.addEdge(s, i, 1);
  for (int i = 1; i <= q; i++) solver.addEdge(p + 2 * n + i, t, 1);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= p; j++) {
      int u;
      std::cin >> u;
      if (u) solver.addEdge(j, p + i, 1);
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= q; j++) {
      int u;
      std::cin >> u;
      if (u) solver.addEdge(p + n + i, p + 2 * n + j, 1);
    }
  }
  std::cout << solver.maxFlow(s, t) << "\n";

  return 0;
}