/**
 * @file    P1791 [国家集训队] 人员雇佣.cpp
 * @author  ForgotDream
 * @brief   最小割
 * @date    2023-08-17
 */
#include <iostream>
#include <vector>
#include <cstring>
#include <queue>

using i64 = long long;

constexpr int N = 1005;
int n;
int a[N], e[N][N];

#pragma region
template<int N = 100050>
struct Dinic {
  struct Edge {
    int u, v, cap, flow;
    Edge(int _u = 0, int _v = 0, int _c = 0) {
      u = _u, v = _v, cap = _c, flow = 0;
    }
  };
  int s, t;
  std::vector<Edge> edges;
  std::vector<int> adj[N];
  int dis[N], cur[N];
  Dinic() = default;
  void addEdge(int u, int v, int cap) {
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
  int dfs(int u, int lim) {
    if (u == t || !lim) return lim;
    int res = 0;
    for (int &i = cur[u], f; i < adj[u].size(); i++) {
      auto &[_, v, cap, flow] = edges[adj[u][i]];
      if (dis[v] == dis[u] + 1 && (f = dfs(v, std::min(lim, cap - flow))) > 0) {
        flow += f, edges[adj[u][i] ^ 1].flow -= f;
        res += f, lim -= f;
        if (!lim) break;
      }
    }
    return res;
  }
  int maxFlow(int s, int t) {
    this->s = s, this->t = t;
    int res = 0;
    while (bfs()) res += dfs(s, 1e9);
    return res;
  }
};
Dinic solver;
#pragma endregion

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n;
  int s = 0, t = n + 1, sum = 0;

  for (int i = 1; i <= n; i++) {
    std::cin >> a[i];
    solver.addEdge(i, t, a[i]);
  }
  for (int i = 1; i <= n; i++) {
    int cur = 0;
    for (int j = 1; j <= n; j++) {
      std::cin >> e[i][j];
      cur += e[i][j];
      solver.addEdge(i, j, 2 * e[i][j]);
    }
    sum += cur;
    solver.addEdge(s, i, cur);
  }

  std::cout << sum - solver.maxFlow(s, t) << "\n";

  return 0;
}