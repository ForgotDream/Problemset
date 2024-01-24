/*
 * @file    P2766 最长不下降子序列问题.cpp
 * @author  ForgotDream
 * @brief   Max Flow + DP
 * @date    2024-01-24
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 2050, inf = 0x3f3f3f3f;

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

int n, a[N], f[N];

void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i];

  if (n == 1) {
    std::cout << "1\n1\n1\n";
    return;
  }

  for (int i = 1; i <= n; i++) {
    for (int j = i; j >= 1; j--) {
      if (a[j] > a[i]) continue;
      f[i] = std::max(f[i], f[j] + 1);
    }
  }

  int len = *std::max_element(f + 1, f + n + 1);
  std::cout << len << "\n";

  int s = 0, t = 2 * n + 1;
  for (int i = 1; i <= n; i++) {
    if (f[i] == 1) solver.add_edge(s, i, 1);
    if (f[i] == len) solver.add_edge(i + n, t, 1);
    solver.add_edge(i, i + n, 1);
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= i; j++) {
      if (a[j] > a[i] || f[i] != f[j] + 1) continue;
      solver.add_edge(j + n, i, 1);
    }
  }

  int ans = solver.max_flow(s, t);
  std::cout << ans << "\n";

  solver.add_edge(1, 1 + n, inf);
  solver.add_edge(s, 1, inf);

  if (f[n] == len) {
    solver.add_edge(n, n + n, inf);
    solver.add_edge(n + n, t, inf);
  }

  std::cout << ans + solver.max_flow(s, t) << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
