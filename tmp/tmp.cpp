/**
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2023-04-28
 */
#include <bits/stdc++.h>

using i64 = long long;
using i64u = unsigned long long;
using f80 = long double;

namespace Helper {
void useFileInuput() {
  #ifndef ONLINE_JUDGE
  freopen("tmp.in", "r", stdin);
  freopen("tmp.out", "w", stdout);
  #endif
  return;
}

void debug(const std::string &s) {
  std::clog << s << "\n";
  return;
}
}

struct Graph {
  static constexpr int INF = 1e9;
  struct Edge {
    int u, v, w;
    Edge(int _u = 0, int _v = 0, int _w = 0) : u(_u), v(_v), w(_w) {}
  };
  int n;
  std::vector<Edge> edges;
  std::vector<std::vector<int>> e;
  std::vector<int> in;

  Graph(int _n) : n(_n) {
    e.resize(n);
    in.resize(n);
    return;
  }

  void add(int u, int v, int w) {
    edges.emplace_back(u, v, w);
    e[u].push_back(edges.size() - 1);
    return;
  }

  std::vector<int> topoSort() {
    std::vector<int> dis(n, -INF);
    std::queue<int> q;

    q.push(0), dis[0] = 0;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (auto i : e[u]) {
        int v = edges[i].v, w = edges[i].w;
        if (!--in[v]) {
          q.push(v);
        }
        dis[v] = std::max(dis[v], dis[u] + w);
      }
    }

    return dis;
  }

  void addIn(int u) {
    in[u]++;
    return;
  }

  std::vector<int> solve() {
    std::vector<int> res, dfn(n), low(n);
    int clk = 0;

    std::function<void(int, int)> tarjan = [&](int u, int rt) {
      low[u] = dfn[u] = ++clk;
      int child = 0;

      for (auto i : e[u]) {
        int v = edges[i].v;
        if (!dfn[v]) {
          tarjan(v, rt);
          low[u] = std::min(low[u], low[v]);
          child += (u == rt);
          if (low[v] >= dfn[u] && u != rt) {
            res.push_back(u);
          }
        } else {
          low[u] = std::min(low[u], dfn[v]);
        }
      }

      if (child >= 2 && u == rt) {
        res.push_back(u);
      }

      return;
    };

    tarjan(0, 0);

    return res;
  }
  
};

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  Graph g(n + 2), rev(n + 2);
  // rev is the reverse graph of the original graph.
  // it's used to build another graph which only contains the special vertexes and edges
  // on the longest path of the original graph.
  std::vector to(n + 2, std::vector<int>());
  std::vector<int> t(n + 1);
  for (int i = 1; i <= n; i++) {
    int c;
    std::cin >> t[i] >> c;
    if (c == 0) {
      g.add(0, i, 0), rev.add(i, 0, 0);
      g.addIn(i);
    } else {
      while (c--) {
        int v;
        std::cin >> v;
        to[v].push_back(i);
        g.addIn(i);
      }
    }
    g.add(i, n + 1, t[i]), rev.add(n + 1, i, t[i]);
    g.addIn(n + 1);
  }

  for (int i = 1; i <= n; i++) {
    for (auto j : to[i]) {
      g.add(i, j, t[i]), rev.add(j, i, t[i]);
    }
  }

  auto dis = g.topoSort();

  Graph rst(n + 2);  // the graph mentioned above.
  std::queue<int> q;

  q.push(n + 1);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (auto i : rev.e[u]) {
      int v = rev.edges[i].v, w = rev.edges[i].w;
      if (dis[u] == dis[v] + w) {
        rst.add(u, v, w), rst.add(v, u, w);
        q.push(v);
      }
    }
  }

  auto ans = rst.solve();
  std::sort(ans.begin(), ans.end());

  std::cout << dis[n + 1] << "\n";
  std::cout << ans.size() << "\n";
  for (int i = 0; i < ans.size(); i++) {
    std::cout << ans[i] << " \n"[i == ans.size() - 1];
  }

  return 0;
}