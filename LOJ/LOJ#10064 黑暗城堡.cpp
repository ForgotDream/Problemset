/**
 * @file    LOJ#10064 黑暗城堡.cpp
 * @author  ForgotDream
 * @brief   SSSP
 * @date    2023-04-16
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
  int n, m;
  std::vector<std::vector<std::pair<int, int>>> e;

  Graph(int n, int m) : n(n), m(m) {
    e.resize(n + 1);
    return;
  }

  void add(int u, int v, int w) {
    e[u].emplace_back(v, w);
    e[v].emplace_back(u, w);
    return;
  }

  std::vector<int> dijkstra(const int &s) {
    std::priority_queue<std::pair<int, int>,
                        std::vector<std::pair<int, int>>, 
                        std::greater<std::pair<int, int>>> pq;
    std::vector<int> dis(n + 1, INT_MAX);
    std::vector<bool> vis(n + 1, false);

    dis[s] = 0;
    pq.emplace(0, s);

    while (!pq.empty()) {
      int u = pq.top().second;
      pq.pop();
      if (vis[u]) {
        continue;
      }
      vis[u] = true;
      for (auto i : e[u]) {
        int v = i.first, w = i.second;
        if (dis[v] > dis[u] + w) {
          dis[v] = dis[u] + w;
          pq.emplace(dis[v], v);
        }
      }
    }

    return dis;
  }

  void solve() {
    auto dis = dijkstra(1);

    std::vector<int> deg(n + 1);
    for (int u = 1; u <= n; u++) {
      for (auto i : e[u]) {
        int v = i.first, w = i.second;
        if (dis[v] == dis[u] + w) {
          deg[v]++;
        }
      }
    }

    i64 ans = 1;
    for (int i = 2; i <= n; i++) {
      (ans *= deg[i]) %= INT_MAX;
    }

    std::cout << ans << "\n";

    return;
  }
};

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  Graph g(n, m);
  for (int i = 0; i < m; i++) {
    int u, v, w;
    std::cin >> u >> v >> w;
    if (u == v) {
      continue;
    }
    g.add(u, v, w);
  }

  g.solve();

  return 0;
}