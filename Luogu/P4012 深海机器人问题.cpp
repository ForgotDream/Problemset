/**
 * @file    P4012 深海机器人问题.cpp
 * @author  ForgotDream
 * @brief   MCMF
 * @date    2023-08-19
 */
#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>

using i64 = long long;
using pll = std::pair<i64, i64>;

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

int a, b, P, Q;

int enc(int i, int j) { return (i - 1) * Q + j; }

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> a >> b >> P >> Q;
  P++, Q++;
  for (int i = 1; i <= P; i++) {
    for (int j = 1; j < Q; j++) {
      int u;
      std::cin >> u;
      solver.addEdge(enc(i, j), enc(i, j + 1), 1, -u);
      solver.addEdge(enc(i, j), enc(i, j + 1), 1e9, 0);
    }
  }
  for (int j = 1; j <= Q; j++) {
    for (int i = 1; i < P; i++) {
      int u;
      std::cin >> u;
      solver.addEdge(enc(i, j), enc(i + 1, j), 1, -u);
      solver.addEdge(enc(i, j), enc(i + 1, j), 1e9, 0);
    }
  }

  int S = 0, T = P * Q + 1;
  for (int i = 1; i <= a; i++) {
    int k, x, y;
    std::cin >> k >> x >> y;
    x++, y++;
    solver.addEdge(S, enc(x, y), k, 0);
  }
  for (int i = 1; i <= b; i++) {
    int k, x, y;
    std::cin >> k >> x >> y;
    x++, y++;
    solver.addEdge(enc(x, y), T, k, 0);
  }

  auto [flow, cost] = solver.solve(S, T);
  std::cout << -cost << "\n";

  return 0;
}