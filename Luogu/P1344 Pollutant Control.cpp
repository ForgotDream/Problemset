/**
 * @file    P1344 Pollutant Control.cpp
 * @author  ForgotDream
 * @brief   Max Flow
 * @date    2023-05-11
 */
#include <bits/stdc++.h>

using i64 = long long;

struct Dinic {
  static constexpr i64 INF = 1e13;
  int n;
  struct Edge {
    int u, v;
    i64 cap, flow;
    Edge(int _u = 0, int _v = 0, i64 _c = 0) {
      u = _u, v = _v, cap = _c, flow = 0;
    }
  };
  std::vector<Edge> edges;
  std::vector<std::vector<int>> g;
  std::vector<int> dis, cur;
  int s, t;

  Dinic(int _n) {
    n = _n;
    g.resize(n + 1);
    dis.resize(n + 1), cur.resize(n + 1);
  }

  void add(int u, int v, i64 cap) {
    edges.emplace_back(u, v, cap);
    edges.emplace_back(v, u, 0);
    g[u].push_back(edges.size() - 2);
    g[v].push_back(edges.size() - 1);
  }

  bool bfs() {
    std::vector<bool> vis(n + 1);
    std::queue<int> q;
    cur.assign(n + 1, 0);

    dis[s] = 0, vis[s] = true;
    q.push(s);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (auto i : g[u]) {
        int v = edges[i].v;
        i64 cap = edges[i].cap, flow = edges[i].flow;
        if (vis[v] || flow >= cap) {
          continue;
        }
        vis[v] = true;
        dis[v] = dis[u] + 1;
        q.push(v);
      }
    }

    return vis[t];
  }

  i64 dfs(int u, i64 flow) {
    if (u == t || !flow) {
      return flow;
    }
    i64 res = 0;
    for (int &i = cur[u]; i < g[u].size(); i++) {
      Edge &curEdge = edges[g[u][i]], &revEdge = edges[g[u][i] ^ 1];
      int v = curEdge.v;
      i64 t, cap = curEdge.cap, f = curEdge.flow;
      if (dis[v] == dis[u] + 1 && (t = dfs(v, std::min(flow, cap - f))) > 0) {
        curEdge.flow += t, revEdge.flow -= t;
        res += t, flow -= t;
      }
    }
    return res;
  }

  i64 maxFlow(int s, int t) {
    this->s = s, this->t = t;
    i64 res = 0;
    while (bfs()) {
      res += dfs(s, INF);
    }
    return res;
  }
};

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  constexpr int D = 2333;

  int n, m;
  std::cin >> n >> m;

  Dinic solver(n);

  for (int i = 0; i < m; i++) {
    int u, v;
    i64 w;
    std::cin >> u >> v >> w;
    solver.add(u, v, D * w + 1);
  }

  i64 flow = solver.maxFlow(1, n);
  std::cout << flow / D << " " << flow % D << "\n";
  
  return 0;
}