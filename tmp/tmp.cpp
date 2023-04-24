/**
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2023-04-24
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
  struct Edge {
    int u, v, w;
    Edge (const int &u, const int &v, const int &w) : u(u), v(v), w(w) {
      return;
    }
  };
  std::vector<Edge> edges;
  int n;
  std::vector<std::vector<int>> e;

  Graph(const int &n) : n(n + 1) {
    e.resize(n + 1);
    return;
  }

  void add(int u, int v, int w) {
    edges.emplace_back(u, v, w);
    edges.emplace_back(v, u, w);
    e[u].emplace_back(edges.size() - 2);
    e[v].emplace_back(edges.size() - 1);
    return;
  }

  std::vector<int> dijkstra(const int &s) {
    std::vector<int> dis(n, 1e9);
    std::vector<bool> vis(n, false);

    std::priority_queue<
      std::pair<int, int>,
      std::vector<std::pair<int, int>>,
      std::greater<std::pair<int, int>>
    > pq;

    pq.emplace(0, s);
    dis[s] = 0;
    while (!pq.empty()) {
      int u = pq.top().second;
      pq.pop();
      if (vis[u]) {
        continue;
      }
      vis[u] = true;
      for (auto i : e[u]) {
        int v = edges[i].v, w = edges[i].w;
        if (dis[v] > dis[u] + w) {
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

  int n, m;
  std::cin >> n >> m;

  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  return 0;
}