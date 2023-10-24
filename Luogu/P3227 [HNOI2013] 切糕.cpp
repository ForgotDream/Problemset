/**
 * @file    P3227 [HNOI2013] 切糕.cpp
 * @author  ForgotDream
 * @brief   最小割
 * @date    2023-08-17
 */
#include <iostream>
#include <vector>
#include <cstring>
#include <queue>

using i64 = long long;

constexpr int N = 50;
constexpr int D[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int p, q, r, d;
i64 f[N][N][N];

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

int encode(int i, int j, int k) { return i * 40 * 40 + j * 40 + k; }
bool valid(int i, int j, int k) {
  return 1 <= i && i <= p && 1 <= j && j <= q && 1 <= k && k <= r;
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> p >> q >> r >> d;
  int s = 0, t = encode(p, q, r) + 1;

  for (int k = 1; k <= r; k++) {
    for (int i = 1; i <= p; i++) {
      for (int j = 1; j <= q; j++) {
        std::cin >> f[i][j][k];
      }
    }
  }

  for (int i = 1; i <= p; i++) {
    for (int j = 1; j <= q; j++) {
      solver.addEdge(s, encode(i, j, 1), 1e9);
    }
  }
  for (int k = 1; k < r; k++) {
    for (int i = 1; i <= p; i++) {
      for (int j = 1; j <= q; j++) {
        solver.addEdge(encode(i, j, k), encode(i, j, k + 1), f[i][j][k]);
        if (k <= d) continue;
        for (int t = 0; t < 4; t++) {
          int dx = i + D[t][0], dy = j + D[t][1];
          if (!valid(dx, dy, k - d)) continue;
          solver.addEdge(encode(i, j, k), encode(dx, dy, k - d), 1e9);
        }
      }
    }
  }
  for (int i = 1; i <= p; i++) {
    for (int j = 1; j <= q; j++) {
      solver.addEdge(encode(i, j, r), t, f[i][j][r]);
      if (r <= d) continue;
      for (int t = 0; t < 4; t++) {
        int dx = i + D[t][0], dy = j + D[t][1];
        if (!valid(dx, dy, r - d)) continue;
        solver.addEdge(encode(i, j, r), encode(dx, dy, r - d), 1e9);
      }
    }
  }

  std::cout << solver.maxFlow(s, t) << "\n";

  return 0;
}