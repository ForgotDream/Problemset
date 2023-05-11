/**
 * @file    P2446 大陆争霸.cpp
 * @author  ForgotDream
 * @brief   Dijkstra
 * @date    2023-05-11
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr i64 INF = 1e18;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<std::pair<int, i64>>> g(n + 1), t(n + 1);
  for (int i = 0; i < m; i++) {
    int u, v;
    i64 w;
    std::cin >> u >> v >> w;
    g[u].emplace_back(v, w);
  }

  std::vector<int> in(n + 1);
  for (int i = 1; i <= n; i++) {
    int k;
    std::cin >> k;
    in[i] = k;
    while (k--) {
      int c;
      std::cin >> c;
      t[c].emplace_back(i, 0);
    }
  }

  auto dijkstra = [&](int s) -> i64 {
    std::vector<i64> d1(n + 1, INF), d2(n + 1);
    std::vector<bool> vis(n + 1);
    std::priority_queue<
      std::pair<i64, int>,
      std::vector<std::pair<i64, int>>,
      std::greater<std::pair<i64, int>>
    > pq;

    d1[s] = d2[s] = 0, pq.emplace(0, s);
    while (!pq.empty()) {
      int u = pq.top().second;
      pq.pop();
      if (vis[u]) {
        continue;
      }
      vis[u] = true;
      for (auto i : t[u]) {
        int v = i.first;
        in[v]--;
        d2[v] = std::max({d2[v], d1[u], d2[u]});
        if (!in[v]) {
          pq.emplace(std::max(d1[v], d2[v]), v);
        }
      }
      for (auto i : g[u]) {
        int v = i.first;
        i64 w = i.second;
        if (d1[v] > std::max(d1[u], d2[u]) + w) {
          d1[v] = std::max(d1[u], d2[u]) + w;
          if (!in[v]) {
            pq.emplace(std::max(d1[v], d2[v]), v);
          }
        }
      }
    }

    return std::max(d1[n], d2[n]);
  };

  auto dis = dijkstra(1);
  std::cout << dis << "\n";

  return 0;
}