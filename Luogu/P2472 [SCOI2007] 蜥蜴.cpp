/*
 * @file    P2472 [SCOI2007] 蜥蜴.cpp
 * @author  ForgotDream
 * @brief   Max Flow
 * @date    2024-01-24
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 2050, inf = 0x3f3f3f3f;

struct Dinic {
  struct Edge {
    int u, v, cap, flow;
    Edge() = default;
    Edge(int _u, int _v, int _c) : u(_u), v(_v), cap(_c), flow(0) {}
  };
  std::vector<Edge> edges;
  int cnt, s, t;
  std::vector<int> adj[N];

  void add_edge(int u, int v, int cap) {
    edges.emplace_back(u, v, cap);
    edges.emplace_back(v, u, 0);
    adj[u].push_back(edges.size() - 2);
    adj[v].push_back(edges.size() - 1);
  }

  int dis[N];
  u32 cur[N];
  bool vis[N];

  bool bfs() {
    std::queue<int> q;
    memset(dis, 0x3f, sizeof(dis));

    dis[s] = 0, q.push(s);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (auto i : adj[u]) {
        auto [_, v, cap, flow] = edges[i];
        if (dis[v] == inf && cap > flow) {
          dis[v] = dis[u] + 1;
          q.push(v);
        }
      }
    }

    return dis[t] < inf;
  }

  int dfs(int u, int lim) {
    if (u == t || !lim) return lim;

    int res = 0;
    for (u32 &i = cur[u]; i < adj[u].size(); i++) {
      auto &[_, v, cap, flow] = edges[adj[u][i]];
      int f;
      if (dis[v] == dis[u] + 1 && cap > flow &&
          (f = dfs(v, std::min(lim, cap - flow))) > 0) {
        res += f, flow += f;
        lim -= f, edges[adj[u][i] ^ 1].flow -= f;
        if (!lim) break;
      }
    }

    return res;
  }

  int max_flow(int _s, int _t) {
    s = _s, t = _t;

    int flow = 0;
    while (bfs()) memset(cur, 0, sizeof(cur)), flow += dfs(s, inf);

    return flow;
  }
} solver;

int n, m, d;

void solve() {
  std::cin >> n >> m >> d;

#define enc(i, j) ((i - 1) * m + j)

  int s = 0, t = 2 * n * m + 1;
  for (int i = 1; i <= n; i++) {
    char c;
    for (int j = 1; j <= m; j++) {
      std::cin >> c;
      solver.add_edge(enc(i, j), enc(i, j) + n * m, c - '0');
    }
  }
  int cnt = 0;
  for (int i = 1; i <= n; i++) {
    char c;
    for (int j = 1; j <= m; j++) {
      std::cin >> c;
      if (c != 'L') continue;
      solver.add_edge(s, enc(i, j), 1);
      cnt++;
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (i <= d || j <= d || i > n - d || j > m - d) {
        solver.add_edge(enc(i, j) + n * m, t, inf);
      }
      for (int k = 1; k <= n; k++) {
        for (int l = 1; l <= m; l++) {
          if (i == k && j == l) continue;
          if (std::hypot(i - k, j - l) > d) continue;
          solver.add_edge(enc(i, j) + n * m, enc(k, l), inf);
          // std::cerr << i << " " << j << " " << k << " " << l << "\n";
        }
      }
    }
  }

#undef enc

  std::cout << cnt - solver.max_flow(s, t) << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
