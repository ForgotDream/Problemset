/**
 * @file    SP1437 PT07Z - Longest path in a tree.cpp
 * @author  ForgotDream
 * @brief   Tree Diameter
 * @date    2023-05-09
 */
#include <bits/stdc++.h>

using i64 = long long;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int n;
  std::cin >> n;

  std::vector<std::vector<int>> g(n + 1);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    std::cin >> u >> v;
    g[u].push_back(v), g[v].push_back(u);
  }

  std::vector<int> dis(n + 1);
  std::function<void(int, int)> dfs = [&](int u, int frm) {
    dis[u] = dis[frm] + 1;
    for (auto v : g[u]) {
      if (v == frm) {
        continue;
      }
      dfs(v, u);
    }
    return;
  };

  dfs(1, 0);
  int pivot = 0;
  for (int i = 1; i <= n; i++) {
    if (dis[pivot] < dis[i]) {
      pivot = i;
    }
  }
  dfs(pivot, 0);
  std::cout << *max_element(dis.begin(), dis.end()) - 1 << "\n";

  return 0;
}