/**
 * @file    P1251 餐巾计划问题.cpp
 * @author  ForgotDream
 * @brief   MCMF
 * @date    2023-08-18
 */
#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>

using i64 = long long;
using pll = std::pair<i64, i64>;

int N, p, m, f, n, s;

#pragma region
template<int N = 4050>
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
  int cur[N];
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
    std::memset(cur, 0, sizeof(cur));
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
    // std::cerr << u << "\n";
    i64 res = 0;
    vis[u] = true;
    for (int &i = cur[u]; i < adj[u].size(); i++) {
      auto &[_, v, cap, flow, w] = edges[adj[u][i]];
      i64 f;
      if (!vis[v] && dis[v] == dis[u] + w &&
          (f = dfs(v, std::min(lim, cap - flow), cost)) > 0) {
        flow += f, edges[adj[u][i] ^ 1].flow -= f;
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

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;
  int S = 0, T = 2 * N + 1;

  for (int i = 1, cap; i <= N; i++)  {
    std::cin >> cap;
    solver.addEdge(S, i + N, cap, 0);
    solver.addEdge(i, T, cap, 0);
  }

  std::cin >> p >> m >> f >> n >> s;
  for (int i = 1; i <= N; i++) {
    solver.addEdge(S, i, MCMF<>::inf, p);
    if (i + 1 <= N) solver.addEdge(i + N, i + N + 1, MCMF<>::inf, 0);
    if (i + m <= N) solver.addEdge(i + N, i + m, MCMF<>::inf, f);
    if (i + n <= N) solver.addEdge(i + N, i + n, MCMF<>::inf, s);
  }

  auto [flow, cost] = solver.solve(S, T);
  std::cout << cost << "\n";

  return 0;
}