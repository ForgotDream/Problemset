/**
 * @file    P1935 [国家集训队] 圈地计划.cpp
 * @author  ForgotDream
 * @brief   最大流
 * @date    2023-08-17
 */
#include <iostream>
#include <vector>
#include <cstring>
#include <queue>

using i64 = long long;

constexpr int N = 105;
constexpr int d[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int n, m;
int a[N][N], b[N][N], c[N][N];

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

  std::cin >> n >> m;
  int s = 0, t = n * m + 1;
  int sum = 0;

  auto encode = [&](int i, int j) { return (i - 1) * m + j; };
  auto valid = [&](int i, int j) { return 1 <= i && i <= n && 1 <= j && j <= m; };

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      std::cin >> a[i][j];
      sum += a[i][j];
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      std::cin >> b[i][j];
      sum += b[i][j];
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if ((i + j) % 2) std::swap(a[i][j], b[i][j]);
      solver.addEdge(s, encode(i, j), a[i][j]);
      solver.addEdge(encode(i, j), t, b[i][j]);
    }
  }
  int cnt = n * m + 1;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      std::cin >> c[i][j];
      int cur = encode(i, j);
      for (int k = 0; k < 4; k++) {
        int dx = i + d[k][0], dy = j + d[k][1];
        if (!valid(dx, dy)) continue;
        sum += 2 * c[i][j];
        int nxt = encode(dx, dy);
        solver.addEdge(s, ++cnt, c[i][j]);
        solver.addEdge(cnt, cur, 1e9);
        solver.addEdge(cnt, nxt, 1e9);
        solver.addEdge(++cnt, t, c[i][j]);
        solver.addEdge(cur, cnt, 1e9);
        solver.addEdge(nxt, cnt, c[i][j]);
      }
    }
  }

  std::cout << sum - solver.maxFlow(s, t) << "\n";

  return 0;
}