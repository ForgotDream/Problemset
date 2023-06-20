/**
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2023-06-19
 */
#include <bits/stdc++.h>

using i64 = long long;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<int>> adj(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    std::cin >> u >> v;
    u--, v--;
    adj[u].push_back(v), adj[v].push_back(u);
  }

  std::vector<i64> f(n), g(n), preVal(n), nxtVal(n);
  std::vector<int> fa(n), prePointer(n), nxtPointer(n);
  std::function<void(int, int)> dfs = [&](int u, int frm) {
    f[u] = g[u] = 1, fa[u] = frm;
    for (auto v : adj[u]) {
      if (v == frm) { continue; }
      dfs(v, u);
      (f[u] *= (f[v] + 1)) %= m;
    }
    int pivot = -1;
    for (auto v : adj[u]) {
      if (pivot == -1) {
        
      }
    }
  };

  dfs(0, -1);
  for (int i = 0; i < n; i++) {
    std::cerr << f[i] << " " << g[i] << "\n";
  }

  return 0;
}