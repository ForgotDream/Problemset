/**
 * @file    P4015 运输问题.cpp
 * @author  ForgotDream
 * @brief   费用流 + 带权二分图完美匹配
 * @date    2023-03-07
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

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> m >> n;

  std::vector<int> a(m + 1), b(n + 1);
  for (int i = 1; i <= m; i++) {
    std::cin >> a[i];
  }
  for (int j = 1; j <= n; j++) {
    std::cin >> b[j];
  }

  MCMF minn(2 * (n + m) + 50), maxx(2 * (n + m) + 50);

  for (int i = 1; i <= m; i++) {
    minn.add(i, i + m, a[i], 0);
    maxx.add(i, i + m, a[i], 0);
  }
  for (int j = 1; j <= n; j++) {
    minn.add(j + 2 * m, j + n + 2 * m , b[j], 0);
    maxx.add(j + 2 * m, j + n + 2 * m , b[j], 0);
  }

  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      int cost;
      std::cin >> cost;
      minn.add(i + m, j + 2 * m, INF, cost);
      maxx.add(i + m, j + 2 * m, INF, -1 * cost);
    }
  }

  int s = 0, t = 2 * (n + m) + 1;
  for (int i = 1; i <= m; i++) {
    minn.add(s, i, INF, 0);
    maxx.add(s, i, INF, 0);
  }
  for (int j = 1; j <= n; j++) {
    minn.add(j + 2 * m + n, t, INF, 0);
    maxx.add(j + 2 * m + n, t, INF, 0);
  }

  std::cout << minn.solve(s, t).second << "\n";
  std::cout << -1 * maxx.solve(s, t).second << "\n";

  return 0;
}