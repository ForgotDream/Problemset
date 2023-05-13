/**
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2023-05-13
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int inf = 1e9;
constexpr int d[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

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
  int s = 0, t = n * m + 1;

  Dinic solver(n * m + 1);

  auto encode = [&](int i, int j) {
    return (i - 1) * m + j;
  };

  auto valid = [&](int i, int j) {
    return i >= 1 && i <= n && j >= 1 && j <= m;
  };

  int c, sum = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      std::cin >> c;
      sum += c;
      solver.add(s, encode(i, j), c);
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      std::cin >> c;
      sum += c;
      solver.add(encode(i, j), t, c);
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      std::cin >> c;
      sum += c;
      for (int k = 0; k < 4; k++) {
        int dx = i + d[k][0], dy = j + d[k][1];
        if (!valid(dx, dy)) {
          continue;
        }
        solver.add(encode(i, j), encode(dx, dy), c);
        solver.add(encode(dx, dy), encode(i, j), c);
      }
    }
  }

  std::cout << solver.maxFlow(s, t) << "\n";

  return 0;
}