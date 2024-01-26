/*
 * @file    P4843 清理雪道.cpp
 * @author  ForgotDream
 * @brief   Bounded Flow
 * @date    2024-01-24
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 105, inf = 0x3f3f3f3f;

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

int n, h[N];

void add_limited_edge(int u, int v, int l, int r) {
  solver.add_edge(u, v, r - l);
  h[u] -= l, h[v] += l;
}

void solve() {
  std::cin >> n;

  int s = n + 1, t = n + 2, S = n + 3, T = n + 4;

  for (int i = 1, ct; i <= n; i++) {
    add_limited_edge(s, i, 0, inf);
    add_limited_edge(i, t, 0, inf);

    std::cin >> ct;
    for (int u; ct; ct--) {
      std::cin >> u;
      add_limited_edge(i, u, 1, inf);
    }
  }

  for (int i = 1; i <= n; i++) {
    if (h[i] > 0) solver.add_edge(S, i, h[i]);
    else if (h[i] < 0) solver.add_edge(i, T, -h[i]);
  }

  solver.max_flow(S, T);
  add_limited_edge(t, s, 0, inf);
  solver.max_flow(S, T);

  auto [_, __, cap, flow] = solver.edges.back();
  std::cout << cap - flow << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
