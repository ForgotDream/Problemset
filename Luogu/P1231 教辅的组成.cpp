/*
 * @file    P1231 教辅的组成.cpp
 * @author  ForgotDream
 * @brief   Max Flow
 * @date    2024-01-24
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 4e4 + 50, inf = 0x3f3f3f3f;

struct Dinic {
  struct Edge {
    int u, v, cap, flow;
    Edge() = default;
    Edge(int _u, int _v, int _c) : u(_u), v(_v), cap(_c), flow(0) {}
  };
  std::vector<Edge> edges;
  int cnt, s, t;
  std::vector<int> adj[N];

  void add_edge(int u, int v, int cap) {
    edges.emplace_back(u, v, cap);
    edges.emplace_back(v, u, 0);
    adj[u].push_back(edges.size() - 2);
    adj[v].push_back(edges.size() - 1);
  }

  int dis[N];
  u32 cur[N];
  bool vis[N];

  bool bfs() {
    std::queue<int> q;
    memset(dis, 0x3f, sizeof(dis));

    dis[s] = 0, q.push(s);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (auto i : adj[u]) {
        auto [_, v, cap, flow] = edges[i];
        if (dis[v] == inf && cap > flow) {
          dis[v] = dis[u] + 1;
          q.push(v);
        }
      }
    }

    return dis[t] < inf;
  }

  int dfs(int u, int lim) {
    if (u == t || !lim) return lim;

    int res = 0;
    for (u32 &i = cur[u]; i < adj[u].size(); i++) {
      auto &[_, v, cap, flow] = edges[adj[u][i]];
      int f;
      if (dis[v] == dis[u] + 1 && cap > flow &&
          (f = dfs(v, std::min(lim, cap - flow))) > 0) {
        res += f, flow += f;
        lim -= f, edges[adj[u][i] ^ 1].flow -= f;
        if (!lim) break;
      }
    }

    return res;
  }

  int max_flow(int _s, int _t) {
    s = _s, t = _t;

    int flow = 0;
    while (bfs()) memset(cur, 0, sizeof(cur)), flow += dfs(s, inf);

    return flow;
  }
} solver;

int n1, n2, n3;
int m1, m2;

void solve() {
  std::cin >> n1 >> n2 >> n3;

  int s = 0, t = 2 * n1 + n2 + n3 + 1;

  std::cin >> m1;
  for (int i = 1, u, v; i <= m1; i++) {
    std::cin >> u >> v;
    solver.add_edge(v, u + n2, 1);
  }
  std::cin >> m2;
  for (int i = 1, u, v; i <= m2; i++) {
    std::cin >> u >> v;
    solver.add_edge(u + n1 + n2, v + 2 * n1 + n2, 1);
  }

  for (int i = 1; i <= n1; i++) solver.add_edge(i + n2, i + n1 + n2, 1);
  for (int i = 1; i <= n2; i++) solver.add_edge(s, i, 1);
  for (int i = 1; i <= n3; i++) solver.add_edge(i + 2 * n1 + n2, t, 1);

  auto flow = solver.max_flow(s, t);
  std::cout << flow << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
