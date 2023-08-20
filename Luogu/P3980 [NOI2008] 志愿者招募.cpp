/**
 * @file    P3980 [NOI2008] 志愿者招募.cpp
 * @author  ForgotDream
 * @brief   MCMF
 * @date    2023-08-20
 */
#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>

using i64 = long long;
using pll = std::pair<i64, i64>;

#pragma region
template<int N = 100050>
struct MCMF {
  static constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;
  struct Edge {
    int u, v;
    i64 cap, flow, cost;
    Edge(int _u = 0, int _v = 0, i64 _cap = 0, i64 _cost = 0) {
      u = _u, v = _v, cap = _cap, flow = 0, cost = _cost;
    }
  };
  int s, t;
  std::vector<Edge> edges;
  std::vector<int> adj[N];
  i64 dis[N];
  bool vis[N];
  MCMF() = default;
  void addEdge(int u, int v, i64 cap, i64 cost) {
    edges.emplace_back(u, v, cap, cost);
    edges.emplace_back(v, u, 0, -cost);
    adj[u].push_back(edges.size() - 2);
    adj[v].push_back(edges.size() - 1);
  }
  bool spfa() {
    std::memset(dis, 0x3f, sizeof(dis));
    std::memset(vis, 0, sizeof(vis));
    std::queue<int> q;
    q.push(s), dis[s] = 0;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      vis[u] = false;
      for (auto i : adj[u]) {
        auto [_, v, cap, flow, w] = edges[i];
        if (dis[v] > dis[u] + w && cap > flow) {
          dis[v] = dis[u] + w;
          if (!vis[v]) vis[v] = true, q.push(v);
        }
      }
    }
    return dis[t] != inf;
  }
  i64 dfs(int u, i64 lim, i64 &cost) {
    if (u == t || !lim) return lim;
    i64 res = 0;
    vis[u] = true;
    for (auto i : adj[u]) {
      auto &[_, v, cap, flow, w] = edges[i];
      i64 f;
      if (!vis[v] && dis[v] == dis[u] + w &&
          (f = dfs(v, std::min(lim, cap - flow), cost)) > 0) {
        flow += f, edges[i ^ 1].flow -= f;
        res += f, lim -= f;
        cost += f * w;
        if (!lim) break;
      }
    }
    return res;
  }
  pll solve(int s, int t) {
    this->s = s, this->t = t;
    i64 res = 0, cost = 0;
    while (spfa()) res += dfs(s, 1e9, cost);
    return std::make_pair(res, cost);
  }
};
MCMF solver;
#pragma endregion

constexpr int N = 1050, inf = 1e9;
int S = 0, T = 100050 - 1;
int n, m, a[N];

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) std::cin >> a[i];

  solver.addEdge(S, 1, inf, 0);
  for (int i = 1; i <= n; i++) solver.addEdge(i, i + 1, inf - a[i], 0);
  for (int i = 1; i <= m; i++) {
    int s, t, c;
    std::cin >> s >> t >> c;
    solver.addEdge(s, t + 1, inf, c);
  }
  solver.addEdge(n + 1, T, inf, 0);
  
  auto [flow, cost] = solver.solve(S, T);
  std::cout << cost << "\n";

  return 0;
}