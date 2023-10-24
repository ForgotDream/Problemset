/**
 * @file    LOJ#10075 农场派对.cpp
 * @author  ForgotDream
 * @brief   SSSP
 * @date    2023-04-20
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
};

struct Graph {
  struct Edge {
    int u, v, w;
    Edge(int u = 0, int v = 0, int w = 0) : u(u), v(v), w(w) {}
  };
  int n;
  std::vector<Edge> edges;
  std::vector<std::vector<int>> e;

  Graph(const int &n) : n(n + 1) {
    e.resize(n + 1);
    return;
  }

  void add(int u, int v, int w) {
    edges.emplace_back(u, v, w);
    e[u].push_back(edges.size() - 1);
    return;
  }

  std::vector<int> dijkstra(int s) {
    std::vector<int> dis(n, 1e9);
    std::vector<bool> vis(n, false);
    std::priority_queue<std::pair<int, int>,
                        std::vector<std::pair<int, int>>,
                        std::greater<std::pair<int, int>>> pq;

    dis[s] = 0;
    pq.emplace(0, s);
    while (!pq.empty()) {
      int u = pq.top().second;
      pq.pop();
      if (vis[u]) {
        continue;
      }
      vis[u] = true;
      for (int i : e[u]) {
        int v = edges[i].v, w = edges[i].w;
        if (dis[v] > dis[u] + w) {
          // std::cerr << u << " " << v << " " << w << "\n";
          dis[v] = dis[u] + w;
          pq.emplace(dis[v], v);
        }
      }
    }

    return dis;
  }
};

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m, x;
  std::cin >> n >> m >> x;

  Graph g(n), rev(n);
  for (int i = 0; i < m; i++) {
    int u, v, w;
    std::cin >> u >> v >> w;
    g.add(v, u, w);
    rev.add(u, v, w);
  }

  auto dis = g.dijkstra(x);
  auto revDis = rev.dijkstra(x);
  for (int i = 1; i <= n; i++) {
    dis[i] += revDis[i];
  }
  int max = *std::max_element(dis.begin() + 1, dis.end());
  
  std::cout << max << "\n";

  return 0;
}