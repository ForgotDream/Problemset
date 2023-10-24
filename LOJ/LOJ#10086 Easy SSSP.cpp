/**
 * @file    LOJ#10086 Easy SSSP.cpp
 * @author  ForgotDream
 * @brief   SPFA Check Circle
 * @date    2023-04-28
 */
#include <bits/stdc++.h>

using i64 = long long;
using i64u = unsigned long long;
using f80 = long double;

namespace MyFile {
void useFileInuput() {
  #ifndef ONLINE_JUDGE
  freopen("tmp.in", "r", stdin);
  freopen("tmp.out", "w", stdout);
  #endif
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

  Graph(int _n) : n(_n) {
    e.resize(n);
    return;
  }

  void add(int u, int v, int w) {
    edges.emplace_back(u, v, w);
    e[u].push_back(edges.size() - 1);
    return;
  }

  auto bfs_spfa(int s) {
    std::vector dis(n, INF);
    std::vector<bool> vis(n, false);
    std::queue<int> q;

    dis[s] = 0, q.push(s);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      vis[u] = false;
      for (auto i : e[u]) {
        int v = edges[i].v, w = edges[i].w;
        if (dis[v] > dis[u] + w) {
          dis[v] = dis[u] + w;
          if (!vis[v]) {
            vis[v] = true, q.push(v);
          }
        }
      }
    }

    return dis;
  }

  std::vector<int> findCircle(int s) {
    std::vector<bool> inq(n, false), vis(n, false);
    std::vector<int> dis(n, INF);

    std::function<bool(int)> spfa = [&](int u) -> bool {
      inq[u] = true, vis[u] = true;

      for (auto i : e[u]) {
        int v = edges[i].v, w = edges[i].w;
        if (dis[v] > dis[u] + w) {
          dis[v] = dis[u] + w;
          if (inq[v]) {
            return true;
          } else if (spfa(v)) {
            return true;
          }
        }
      }

      inq[u] = false;
      return false;
    };

    if (spfa(0)) {
      return std::vector<int>();
    } else {
      return bfs_spfa(s);
    }
  }
  
};

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  constexpr int INF = 1e9;
  
  int n, m, s;
  std::cin >> n >> m >> s;

  Graph g(n + 1);
  for (int i = 0; i < m; i++) {
    int u, v, w;
    std::cin >> u >> v >> w;
    g.add(u, v, w);
  }

  for (int i = 1; i <= n; i++) {
    g.add(0, i, -1);
  }

  auto dis = g.findCircle(s);

  if (dis.empty()) {
    std::cout << -1 << "\n";
  } else {
    for (int i = 1; i <= n; i++) {
      if (dis[i] != INF) {
        std::cout << dis[i] << "\n";
      } else {
        std::cout << "NoPath\n";
      }
    }
  }

  return 0;
}