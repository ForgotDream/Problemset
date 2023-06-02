/**
 * @file    P2153 晨跑.cpp
 * @author  ForgotDream
 * @brief   MCMF
 * @date    2023-05-15
 */
#include <bits/stdc++.h>

using i64 = long long;

struct MCMF {
  struct Edge {
    int from, to, cap, cost;
    Edge(int u, int v, int cap, int cost) 
      : from(u), to(v), cap(cap), cost(cost) {}
  };
  static const int INF = 0x3f3f3f3f;
  int n, s, t;
  std::vector<Edge> edge;
  std::vector<std::vector<int>> e;
  std::vector<int> cur, dis;
  std::vector<bool> vis;

  MCMF(const int &n) {
    this->n = n;
    e.resize(n);
    cur.resize(n);
    dis.resize(n);
    vis.resize(n);
    return;
  }

  bool spfa(int s, int t) {
    std::fill(dis.begin(), dis.end(), INF);
    std::fill(vis.begin(), vis.end(), false);
    std::fill(cur.begin(), cur.end(), 0);
    std::queue<int> q;

    q.push(s);
    dis[s] = 0;
    vis[s] = true;

    while (!q.empty()) {
      int u = q.front();
      q.pop();
      vis[u] = false;
      for (int i : e[u]) {
        int v = edge[i].to;
        if (edge[i].cap && dis[v] > dis[u] + edge[i].cost) {
          dis[v] = dis[u] + edge[i].cost;
          if (!vis[v]) {
            vis[v] = true;
            q.push(v);
          }
        }
      }
    }

    return dis[t] != INF;
  }

  int dfs(int u, int flow, int &minCost) {
    // std::cerr << u << " " << flow << " " << minCost << "\n";
    if (u == t || flow == 0) {
      return flow;
    }
    int res = 0, tmp;
    vis[u] = true;
    for (int &i = cur[u]; i < e[u].size(); i++) {
      Edge &curEdge = edge[e[u][i]];
      // std::cerr << dis[u] << " " << dis[curEdge.to] << "\n";
      if (!vis[curEdge.to] && dis[curEdge.to] == dis[u] + curEdge.cost && 
          (tmp = dfs(curEdge.to, std::min(curEdge.cap, flow), minCost)) > 0) {
        minCost += tmp * curEdge.cost;
        curEdge.cap -= tmp;
        edge[e[u][i] ^ 1].cap += tmp;
        res += tmp;
        flow -= tmp;
        if (flow == 0) {
          break;
        }
      }
    }
    vis[u] = false;
    return res;
  }

  void add(int u, int v, int cap, int cost) {
    edge.emplace_back(u, v, cap, cost);
    edge.emplace_back(v, u, 0, -1 * cost);

    e[u].push_back(edge.size() - 2);
    e[v].push_back(edge.size() - 1);

    return;
  }

  std::pair<int, int> solve(int s, int t) {
    int flow = 0, cost = 0;
    this->s = s;
    this->t = t;
    while (spfa(s, t)) {
      flow += dfs(s, INF, cost);
    }
    return std::make_pair(flow, cost);
  }
};

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  MCMF solver(2 * n + 1);

  for (int i = 1; i <= n; i++) {
    solver.add(i, i + n, 1, 0);
  }

  for (int i = 0; i < m; i++) {
    int u, v, w;
    std::cin >> u >> v >> w;
    solver.add(u + n, v, 1, w);
  }

  auto p = solver.solve(1 + n, n);
  std::cout << p.first << " " << p.second << "\n";

  return 0;
}