/**
 * @file    AT_dp_g Longest Path.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-06-18
 */
#include <bits/stdc++.h>

using i64 = long long;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<int>> adj(n);
  std::vector<int> deg(n);
  for (int i = 0; i < m; i++) {
    int u, v;
    std::cin >> u >> v;
    u--, v--;
    adj[u].push_back(v), deg[v]++;
  }

  std::queue<int> q;
  for (int i = 0; i < n; i++) {
    if (!deg[i]) { q.push(i); }
  }

  std::vector<int> dis(n);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (auto v : adj[u]) {
      dis[v] = std::max(dis[v], dis[u] + 1);
      if (!--deg[v]) { q.push(v); }
    }
  }

  std::cout << *std::max_element(dis.begin(), dis.end()) << "\n";

  return 0;
}