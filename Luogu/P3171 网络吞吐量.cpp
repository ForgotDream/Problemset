/**
 * @file    P3171 网络吞吐量.cpp
 * @author  ForgotDream
 * @brief   Max Flow + Dijkstra
 * @date    2023-05-11
 */
#include <bits/stdc++.h>
#define int long long

using i64 = long long;

struct Dinic {
  static constexpr int INF = 1e9;
  int n, s, t;
  struct Edge {
    int u, v, cap, flow;
    Edge(int _u, int _v, int _c) {
      u = _u, v = _v, cap = _c, flow = 0;
    }
  };
  std::vector<Edge> edges;
  std::vector<std::vector<int>> g;
  std::vector<int> cur, dis;

  Dinic(int _n) {
    n = _n;
    g.resize(n + 1);
    cur.resize(n + 1), dis.resize(n + 1);
  }

  void add(int u, int v, int c) {
    edges.emplace_back(u, v, c);
    edges.emplace_back(v, u, 0);
    g[u].push_back(edges.size() - 2);
    g[v].push_back(edges.size() - 1);
  }

  bool bfs() {
    std::vector<bool> vis(n + 1);
    cur.assign(n + 1, 0);
    std::queue<int> q;
    q.push(s);
    vis[s] = true, dis[s] = 0;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (auto i : g[u]) {
        int v = edges[i].v, cap = edges[i].cap;
        int flow = edges[i].flow;
        if (!vis[v] && cap > flow) {
          vis[v] = true, dis[v] = dis[u] + 1;
          q.push(v);
        }
      }
    }
    return vis[t];
  }

  int dfs(int u, int flow) {
    if (u == t || flow == 0) {
      return flow;
    }
    int res = 0;
    for (int &i = cur[u]; i < g[u].size(); i++) {
      int t, v = edges[g[u][i]].v;
      int cap = edges[g[u][i]].cap, f = edges[g[u][i]].flow;
      if (dis[v] == dis[u] + 1 && (t = dfs(v, std::min(flow, cap - f))) > 0) {
        edges[g[u][i]].flow += t;
        edges[g[u][i] ^ 1].flow -= t;
        res += t, flow -= t;
        if (!flow) {
          break;
        }
      }
    }
    return res;
  }

  int maxFlow(int s, int t) {
    this->s = s, this->t = t;
    int res = 0;
    while (bfs()) {
      res += dfs(s, INF);
    }
    return res;
  }
};

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  
  constexpr int INF = 1e9;

  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<std::pair<int, int>>> g(n + 1);
  for (int i = 0; i < m; i++) {
    int u, v, w;
    std::cin >> u >> v >> w;
    g[u].emplace_back(v, w);
    g[v].emplace_back(u, w);
  }

  auto dijkstra = [&](int s) {
    std::vector<int> dis(n + 1, INF);
    std::vector<bool> vis(n + 1);
    std::priority_queue<
      std::pair<int, int>,
      std::vector<std::pair<int, int>>,
      std::greater<std::pair<int, int>>
    > pq;

    pq.emplace(0, s);
    dis[s] = 0;
    while (!pq.empty()) {
      int u = pq.top().second;
      pq.pop();
      if (vis[u]) {
        continue;
      }
      vis[u] = true;
      for (auto i : g[u]) {
        int v = i.first, w = i.second;
        if (dis[v] > dis[u] + w) {
          dis[v] = dis[u] + w;
          pq.emplace(dis[v], v);
        }
      }
    }

    return dis;
  };

  auto dis = dijkstra(1);

  Dinic solver(2 * n);
  for (int u = 1; u <= n; u++) {
    for (auto i : g[u]) {
      int v = i.first, w = i.second;
      if (dis[v] == dis[u] + w) {
        solver.add(u + n, v, INF);
      }
    }
  }

  for (int i = 1; i <= n; i++) {
    int c;
    std::cin >> c;
    solver.add(i, i + n, c);
  }

  std::cout << solver.maxFlow(1 + n, n) << "\n";

  return 0;
}