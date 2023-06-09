/**
 * @file    P2018 消息传递.cpp
 * @author  ForgotDream
 * @brief   DP in Tree
 * @date    2023-06-08
 */
#include <bits/stdc++.h>

using i64 = long long;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  std::vector<std::vector<int>> adj(n);
  for (int i = 1; i < n; i++) {
    int u;
    std::cin >> u, u--;
    adj[u].push_back(i), adj[i].push_back(u);
  }

  std::vector<int> f(n);
  std::function<void(int, int)> dfs = [&](int u, int frm) {
    for (auto v : adj[u]) {
      if (v == frm) { continue; }
      dfs(v, u);
    }
    std::sort(adj[u].begin(), adj[u].end(), [&](int lhs, int rhs) {
      return f[lhs] > f[rhs];
    });
    int cnt = 0;
    for (auto v : adj[u]) {
      if (v == frm) { continue; }
      f[u] = std::max(f[u], f[v] + (++cnt));
    }
  };

  std::vector<int> ans(n);
  for (int i = 0; i < n; i++) {
    f.assign(n, 0), dfs(i, -1);
    ans[i] = f[i];
  }

  int min = *min_element(ans.begin(), ans.end());
  std::cout << min + 1 << "\n";
  for (int i = 0; i < n; i++) { 
    if (ans[i] == min) { std::cout << i + 1 << " "; } 
  }

  return 0;
}