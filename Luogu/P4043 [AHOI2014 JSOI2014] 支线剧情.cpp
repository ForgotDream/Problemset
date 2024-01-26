/*
 * @file    P4043 [AHOI2014 JSOI2014] 支线剧情.cpp
 * @author  ForgotDream
 * @brief   Bounded Cost Flow
 * @date    2024-01-24
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 505, inf = 0x3f3f3f3f;

struct MCMF {
  struct Edge {
    int u, v, cap, cost;
    Edge() = default;
    Edge(int _u, int _v, int _c, int _w) : u(_u), v(_v), cap(_c), cost(_w) {}
  };
  std::vector<Edge> edges;
  std::vector<int> adj[N];
  int s, t, dis[N];
  bool vis[N];

  void add_edge(int u, int v, int cap, int cost) {
    edges.emplace_back(u, v, cap, cost);
    edges.emplace_back(v, u, 0, -cost);
    adj[u].push_back(edges.size() - 2);
    adj[v].push_back(edges.size() - 1);
  }

  bool spfa() {
    static bool ins[N];
    std::queue<int> q;
    memset(dis, 0x3f, sizeof(dis));
    memset(ins, false, sizeof(ins));

    dis[s] = 0, q.push(s);
    while (!q.empty()) {
      int u = q.front();
      q.pop(), ins[u] = false;
      for (auto i : adj[u]) {
        auto [_, v, cap, w] = edges[i];
        if (dis[v] > dis[u] + w && cap) {
          dis[v] = dis[u] + w;
          if (!ins[v]) q.push(v), ins[v] = true;
        }
      }
    }

    return dis[t] != inf;
  }

  int dfs(int u, int lim, int &cost) {
    if (u == t || !lim) return lim;
    int res = 0;
    vis[u] = true;
    for (auto i : adj[u]) {
      auto &[_, v, cap, w] = edges[i];
      int f;
      if (dis[v] == dis[u] + w && !vis[v] && 
          (f = dfs(v, std::min(lim, cap), cost)) > 0) {
        cap -= f, lim -= f, cost += f * w;
        res += f, edges[i ^ 1].cap += f;
        if (!lim) break;
      }
    }
    return res;
  }

  std::pair<int, int> solve(int _s, int _t) {
    s = _s, t = _t;
    int flow = 0, cost = 0;

    while (spfa()) {
      memset(vis, false, sizeof(vis));
      flow += dfs(s, inf, cost);
    }

    return {flow, cost};
  }
} solver;

int n, h[N], ans;

void add_limited_edge(int u, int v, int lo, int hi, int cost) {
  solver.add_edge(u, v, hi - lo, cost);
  h[u] -= lo, h[v] += lo, ans += lo * cost;
}

void solve() {
  std::cin >> n;
  
  int s = 1, t = n + 1, S = n + 2, T = n + 3;
  for (int i = 1, ct; i <= n; i++) {
    if (i != 1) add_limited_edge(i, t, 0, inf, 0);
    std::cin >> ct;
    for (int v, w; ct; ct--) {
      std::cin >> v >> w;
      add_limited_edge(i, v, 1, inf, w);
    }
  }

  for (int i = 1; i <= n; i++) {
    if (h[i] > 0) solver.add_edge(S, i, h[i], 0);
    else if (h[i] < 0) solver.add_edge(i, T, -h[i], 0);
  }

  add_limited_edge(t, s, 0, inf, 0);
  auto [flow, cost] = solver.solve(S, T);

  std::cout << ans + cost << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
