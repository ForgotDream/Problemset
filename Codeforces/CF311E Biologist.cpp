/**
 * @file    CF311E Biologist.cpp
 * @author  ForgotDream
 * @brief   最小割
 * @date    2023-08-19
 */
#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>

using i64 = long long;

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

constexpr int N = 1e4 + 50;
int S = 0, T = 100050 - 1;
int n, m, g, a[N], v[N];
std::vector<int> vec;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n >> m >> g;
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i];
  }
  for (int i = 1; i <= n; i++) {
    std::cin >> v[i];
    if (a[i]) solver.addEdge(i, T, v[i]);
    else solver.addEdge(S, i, v[i]);
  }
  
  int sum = 0;
  for (int i = 1; i <= m; i++) {
    int val, w, k;
    bool flg;
    std::cin >> val >> w >> k;
    sum += w;
    for (int j = 1; j <= k; j++) {
      int u;
      std::cin >> u;
      if (val) solver.addEdge(u, n + i, 1e9);
      else solver.addEdge(n + i, u, 1e9);
    }
    std::cin >> flg;
    if (flg) w += g;
    if (val) solver.addEdge(n + i, T, w);
    else solver.addEdge(S, n + i, w);
  }
  
  std::cout << sum - solver.maxFlow(S, T) << "\n";

  return 0;
}