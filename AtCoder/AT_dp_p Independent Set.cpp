/**
 * @file    AT_dp_p Independent Set.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-06-20
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int mod = 1e9 + 7;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  std::vector<std::vector<int>> adj(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    std::cin >> u >> v;
    u--, v--;
    adj[u].push_back(v), adj[v].push_back(u);
  }

  std::vector f(n, std::vector<i64>(2));
  std::function<void(int, int)> dfs = [&](int u, int frm) {
    f[u][0] = f[u][1] = 1;
    for (auto v : adj[u]) {
      if (v == frm) { continue; }
      dfs(v, u);
      (f[u][0] *= f[v][0] + f[v][1]) %= mod;
      (f[u][1] *= f[v][0]) %= mod;
    }
  };

  dfs(0, -1);
  std::cout << (f[0][0] + f[0][1]) % mod << "\n";

  return 0;
}
