/**
 * @file    P2805 植物大战僵尸.cpp
 * @author  ForgotDream
 * @brief   Min Cut
 * @date    2023-05-15
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int inf = 1e9;

struct Dinic {
  int n;
  struct Edge {
    int u, v, cap, flow;
    Edge(int _u = 0, int _v = 0, int _c = 0) {
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

  void add(int u, int v, int cap) {
    edges.emplace_back(u, v, cap);
    edges.emplace_back(v, u, 0);
    g[u].push_back(edges.size() - 2);
    g[v].push_back(edges.size() - 1);
  }

  bool bfs() {
    std::vector<bool> vis(n + 1);
    std::queue<int> q;
    cur.assign(n + 1, 0);

    dis[s] = 0, vis[s] = true, q.push(s);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (auto i : g[u]) {
        int v = edges[i].v, cap = edges[i].cap, flow = edges[i].flow;
        if (vis[v] || flow >= cap) {
          continue;
        }
        vis[v] = true, dis[v] = dis[u] + 1;
        q.push(v);
      }
    }

    return vis[t];
  }

  int dfs(int u, int flow) {
    if (u == t || !flow) {
      return flow;
    }
    int res = 0;
    for (int &i = cur[u]; i < g[u].size(); i++) {
      Edge &curEdge = edges[g[u][i]], &revEdge = edges[g[u][i] ^ 1];
      int t, v = curEdge.v;
      int cap = curEdge.cap, f = curEdge.flow;
      if (dis[v] == dis[u] + 1 && (t = dfs(v, std::min(flow, cap - f))) > 0) {
        curEdge.flow += t, revEdge.flow -= t;
        res += t, flow -= t;
      }
    }
    return res;
  }

  int maxFlow(int s, int t) {
    this->s = s, this->t = t;
    int res = 0;
    while (bfs()) {
      res += dfs(s, inf);
    }
    return res;
  }
};

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  auto convert = [m](int i, int j) { return i * m + j; };

  std::vector<int> score(n * m), in(n * m);
  std::vector<std::vector<int>> g(n * m);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      int t = convert(i, j);
      int w;
      std::cin >> score[t] >> w;
      while (w--) {
        int u, v;
        std::cin >> u >> v;
        g[t].push_back(convert(u, v));
        in[convert(u, v)]++;
      }
      if (j != m - 1) {
        g[convert(i, j + 1)].push_back(t);
        in[t]++;
      }
    }
  }

  std::queue<int> q;
  std::vector<bool> vis(n * m);
  for (int i = 0; i < n * m; i++) {
    if (!in[i]) {
      q.push(i), vis[i] = true;
    }
  }

  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (auto v : g[u]) {
      in[v]--;
      if (!vis[v] && !in[v]) {
        q.push(v), vis[v] = true;
      }
    }
  }

  int s = n * m, t = n * m + 1, sum = 0;
  Dinic solver(n * m + 1);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      int u = convert(i, j);
      std::cerr << u << "\n";
      if (!vis[u]) {
        continue;
      }
      if (score[u] >= 0) {
        sum += score[u];
        solver.add(s, u, score[u]);
      } else {
        solver.add(u, t, -score[u]);
      }
      for (auto v : g[u]) {
        if (vis[v]) {
          solver.add(v, u, inf);
        }
      }
    }
  }

  std::cout << sum - solver.maxFlow(s, t) << "\n";

  return 0;
}