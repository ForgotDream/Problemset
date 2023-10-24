/**
 * @file    P3358 最长k可重区间集问题.cpp
 * @author  ForgotDream
 * @brief   最小费用最大流
 * @date    2023-03-10
 */
#include <bits/stdc++.h>

using i64 = long long;

static const int INF = 0x3f3f3f3f;
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
    if (u == t || flow == 0) {
      return flow;
    }
    int res = 0, tmp;
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
struct Seg {
  int l, r;
  Seg(int l, int r) : l(l), r(r) {}
};

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, k;
  std::cin >> n >> k;
  std::vector<int> a;
  std::vector<Seg> seg;
  for (int i = 1; i <= n; i++) {
    int l, r;
    std::cin >> l >> r;
    a.push_back(l);
    a.push_back(r);
    seg.emplace_back(l, r);
  }

  auto b = a;
  std::sort(b.begin(), b.end());
  b.erase(unique(b.begin(), b.end()), b.end());

  MCMF solver(b.size() + 50);
  int s = b.size() + 1, t = s + 1;
  for (auto i : seg) {
    int l = i.l, r = i.r;
    l = std::lower_bound(b.begin(), b.end(), l) - b.begin() + 1;
    r = std::lower_bound(b.begin(), b.end(), r) - b.begin() + 1;
    solver.add(l, r, 1, i.l - i.r);
  }
  for (int i = 2; i <= b.size(); i++) {
    solver.add(i - 1, i, k, 0);
  }
  solver.add(s, 1, k, 0);
  solver.add(b.size(), t, k, 0);

  std::cout << -1 * solver.solve(s, t).second << "\n";

  return 0;
}