/**
 * @file    P4316 绿豆蛙的归宿.cpp
 * @author  ForgotDream
 * @brief   Expectation + DP
 * @date    2023-06-08
 */
#include <bits/stdc++.h>

using i64 = long long;
using f80 = long double;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout << std::fixed << std::setprecision(2);

  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<std::pair<int, int>>> adj(n);
  std::vector<int> deg(n), in(n);
  for (int i = 0; i < m; i++) {
    int u, v, w;
    std::cin >> u >> v >> w;
    u--, v--;
    adj[v].emplace_back(u, w);
    deg[u]++, in[u]++;
  }

  std::queue<int> q;
  q.push(n - 1);
  std::vector<f80> f(n);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (auto i : adj[u]) {
      int v = i.first, w = i.second;
      f[v] += (f[u] + w) / deg[v];
      if (!--in[v]) { q.push(v); }
    }
  }

  std::cout << f[0] << "\n";

  return 0;
}