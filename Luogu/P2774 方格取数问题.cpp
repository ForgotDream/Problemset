/**
 * @file    P2774 方格取数问题.cpp
 * @author  ForgotDream
 * @brief   最大流
 * @date    2023-08-18
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

// grid graph
constexpr int d[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int n, m;
int encode(int i, int j) { return (i - 1) * m + j; }
bool valid(int i, int j) { return 1 <= i && i <= n && 1 <= j && j <= m; }

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n >> m;
  int sum = 0, S = 0, T = n * m + 1;

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      int u;
      std::cin >> u;
      sum += u;
      if ((i + j) % 2) {
        solver.addEdge(S, encode(i, j), u);
        for (int k = 0; k < 4; k++) {
          int dx = i + d[k][0], dy = j + d[k][1];
          if (!valid(dx, dy)) continue;
          solver.addEdge(encode(i, j), encode(dx, dy), 1e9);
        }
      } else {
        solver.addEdge(encode(i, j), T, u);
      }
    }
  }

  std::cout << sum - solver.maxFlow(S, T) << "\n";

  return 0;
}