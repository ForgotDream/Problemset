/**
 * @file    UVA11613 Acme Corporation.cpp
 * @author  ForgotDream
 * @brief   最大费用任意流
 * @date    2023-03-09
 */
#include <bits/stdc++.h>

using i64 = long long;

static const int INF = 0x3f3f3f3f;
struct MCMF {
  struct Edge {
    int from, to;
    i64 cap, cost;
    Edge(int u, int v, i64 cap, i64 cost) 
      : from(u), to(v), cap(cap), cost(cost) {}
  };
  static const i64 INF = 1e18;
  int n, s, t;
  std::vector<Edge> edge;
  std::vector<std::vector<int>> e;
  std::vector<int> cur;
  std::vector<i64> dis;
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

  i64 dfs(int u, i64 flow, i64 &minCost) {
    if (u == t || flow == 0) {
      return flow;
    }
    i64 res = 0, tmp;
    vis[u] = true;
    for (int &i = cur[u]; i < e[u].size(); i++) {
      Edge &curEdge = edge[e[u][i]];
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

  void add(int u, int v, i64 cap, i64 cost) {
    edge.emplace_back(u, v, cap, cost);
    edge.emplace_back(v, u, 0, -1 * cost);

    e[u].push_back(edge.size() - 2);
    e[v].push_back(edge.size() - 1);

    return;
  }

  std::pair<int, i64> solve(int s, int t) {
    int flow = 0;
    i64 cost = 0, lst = 0;
    this->s = s;
    this->t = t;
    while (spfa(s, t)) {
      lst = cost;
      flow += dfs(s, INF, cost);
      if (cost > lst) {
        break;
      }
    }
    return std::make_pair(flow, lst);
  }
};

void solve(int no) {
  int N;
  i64 W;
  std::cin >> N >> W;
  MCMF solver(2 * N + 50);
  int S = 0, T = 2 * N + 1;
  for (int i = 1; i <= N; i++) {
    i64 m, p;
    int n, s, e;
    std::cin >> m >> n >> p >> s >> e;
    for (int j = 0; i + j <= N && j <= e; j++) {
      solver.add(i, i + j + N, INF, W * j);
    }
    solver.add(S, i, n, m);
    solver.add(i + N, T, s, -1 * p);
  }
  std::cout << "Case " << no << ": " << -1 * solver.solve(S, T).second << "\n";
  return;
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  
  int t;
  std::cin >> t;

  for (int i = 1; i <= t; i++) {
    solve(i);
  }

  return 0;
}