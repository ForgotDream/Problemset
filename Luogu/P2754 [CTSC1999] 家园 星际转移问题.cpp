/**
 * @file    P2754 [CTSC1999] 家园 / 星际转移问题.cpp
 * @author  ForgotDream
 * @brief   最大流
 * @date    2023-08-18
 */
#include <algorithm>
#include <cstring>
#include <iostream>
#include <numeric>
#include <queue>
#include <vector>

using i64 = long long;

// Dinic for maximum flow
#pragma region
template<int N = 1000050>
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
// DSU for checking the existance of answer
#pragma region
template<int N = 25>
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

constexpr int N = 25;
int n, m, k, h[N], r[N];
int path[N][N];

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n >> m >> k;
  int S = 0, T = 1000050 - 1;

  for (int i = 1; i <= m; i++) {
    std::cin >> h[i] >> r[i];
    for (int j = 0; j < r[i]; j++) {
      std::cin >> path[i][j];
      if (path[i][j] == 0) path[i][j] = n + 1;
      if (path[i][j] == -1) path[i][j] = n + 2;
      if (j) dsu.merge(path[i][j], path[i][j - 1]);
    }
  }

  if (dsu.find(n + 1) != dsu.find(n + 2)) return std::cout << 0 << "\n", 0;

  int ans = 1;
  auto convert = [&](int i, int u, bool flg = false) {
    if (path[i][u] == n + 2) return T;
    else return (ans - 1 + flg) * (n + 1) + path[i][u];
  };

  solver.s = S, solver.t = T;

  int flow = 0;
  for (; ; ans++) {
    solver.addEdge(S, (ans - 1) * (n + 1) + n + 1, 1e9);
    for (int i = 1; i <= m; i++) {
      int u = convert(i, (ans - 1) % r[i]);
      int v = convert(i, ans % r[i], true);
      solver.addEdge(u, v, h[i]);
    }
    while (solver.bfs()) flow += solver.dfs(S, 1e9);
    if (flow >= k) break;
    for (int i = 1; i <= n + 1; i++) {
      solver.addEdge((ans - 1) * (n + 1) + i, ans * (n + 1) + i, 1e9);
    }
  }
  std::cout << ans << "\n";

  return 0;
}