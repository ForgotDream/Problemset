/**
 * @file    P1361 小M的作物.cpp
 * @author  ForgotDream
 * @brief   Min Cut
 * @date    2023-05-12
 */
#include <bits/stdc++.h>

using i64 = long long;

struct Dinic {
  static constexpr int INF = 1e9;
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
    q.push(s), dis[s] = 0, vis[s] = true;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (auto i : g[u]) {
        int v = edges[i].v, cap = edges[i].cap, flow = edges[i].flow;
        if (vis[v] || cap <= flow) {
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
      int t, v = curEdge.v, cap = curEdge.cap, f = curEdge.flow;
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
      res += dfs(s, INF);
    }
    return res;
  }
};

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  constexpr int INF = 1e9;

  int n;
  std::cin >> n;

  Dinic solver(3 * n + 1);
  int sum = 0;
  std::vector<int> a(n + 1), b(n + 1);
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i];
    solver.add(0, i, a[i]);
    sum += a[i];
  }
  for (int i = 1; i <= n; i++) {
    std::cin >> b[i];
    solver.add(i, n + 1, b[i]);
    sum += b[i];
  }

  int m;
  std::cin >> m;

  int cnt = n + 1;
  for (int i = 1; i <= m; i++) {
    int k, c1, c2;
    std::cin >> k >> c1 >> c2;
    sum += c1 + c2;
    solver.add(0, cnt + 1, c1);
    solver.add(cnt + 2, n + 1, c2);
    for (int i = 1; i <= k; i++) {
      int c;
      std::cin >> c;
      solver.add(cnt + 1, c, INF);
      solver.add(c, cnt + 2, INF);
    }
    cnt += 2;
  }

  std::cout << sum - solver.maxFlow(0, n + 1) << "\n";

  return 0;
}