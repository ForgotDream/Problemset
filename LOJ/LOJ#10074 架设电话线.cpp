/**
 * @file    LOJ#10074 架设电话线.cpp
 * @author  ForgotDream
 * @brief   SSSP + 二分
 * @date    2023-04-19
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
    Edge(int u, int v, int w) : u(u), v(v), w(w) {}
  };

  int n;
  std::vector<std::vector<int>> e;
  std::vector<Edge> edges;

  Graph(int n) : n(n + 1) {
    e.resize(n + 1);
    return;
  }

  void add(int u, int v, int w) {
    edges.emplace_back(u, v, w);
    edges.emplace_back(v, u, w);
    e[u].push_back(edges.size() - 2);
    e[v].push_back(edges.size() - 1);
    return;  
  }

  int shortestPath(int s, int t, int val) {
    std::vector<int> dis(n, 1e9);
    std::vector<bool> vis(n);
    std::priority_queue<std::pair<int, int>, 
                        std::vector<std::pair<int, int>>, 
                        std::greater<std::pair<int, int>>> pq;

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
        int d = w > val;
        if (dis[v] > dis[u] + d) {
          dis[v] = dis[u] + d;
          pq.emplace(dis[v], v);
        }
      }
    }

    return dis[t];
  }
};

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, p, k;
  std::cin >> n >> p >> k;

  Graph g(n);
  int max = INT_MIN;
  for (int i = 0; i < p; i++) {
    int u, v, w;
    std::cin >> u >> v >> w;
    max = std::max(max, w);
    g.add(u, v, w);
  }

  int L = 0, R = max + 1, ans = INT_MAX;
  while (L <= R) {
    int mid = (L + R) >> 1, f;
    if ((f = g.shortestPath(1, n, mid)) <= k) {
      R = mid - 1;
      ans = mid;
    } else {
      L = mid + 1;
    }
  }

  if (ans == INT_MAX) {
    std::cout << -1 << "\n";
  } else {
    std::cout << ans << "\n";
  }

  return 0;
}