/**
 * @file    P5521 梅深不见冬.cpp
 * @author  ForgotDream
 * @brief   Greedy + DFS
 * @date    2023-05-13
 */
#include <bits/stdc++.h>

using i64 = long long;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  std::vector<int> p(n + 1);
  std::vector<std::vector<int>> g(n + 1);
  for (int i = 2; i <= n; i++) {
    std::cin >> p[i];
    g[p[i]].push_back(i);
  }

  std::vector<int> w(n + 1);
  for (int i = 1; i <= n; i++) {
    std::cin >> w[i];
  }

  std::vector<int> ans(n + 1), son(n + 1), rst(n + 1);
  std::function<void(int, int)> dfs = [&](int u, int frm) {
    for (auto v : g[u]) {
      dfs(v, u);
      son[u] += w[v];
    }
    if (!son[u]) {
      ans[u] = w[u];
      rst[u] = 0;
      return;
    }
    std::sort(g[u].begin(), g[u].end(), [&](const int &lhs, const int &rhs) {
      return ans[lhs] - w[lhs] > ans[rhs] - w[rhs];
    });
    rst[u] = ans[g[u][0]] - w[g[u][0]];
    int d = ans[g[u][0]];
    for (int i = 1; i < g[u].size(); i++) {
      d += std::max(0, ans[g[u][i]] - rst[u]);
      rst[u] = std::max(0, rst[u] - ans[g[u][i]]) + rst[g[u][i]] + son[g[u][i]];
    }
    d += std::max(w[u] - rst[u], 0);
    rst[u] = std::max(0, rst[u] - w[u]);
    ans[u] = d;
  };

  dfs(1, 0);

  for (int i = 1; i <= n; i++) {
    std::cerr << rst[i] << " \n"[i == n];
  }

  for (int i = 1; i <= n; i++) {
    std::cout << ans[i] << " \n"[i == n];
  }

  return 0;
}