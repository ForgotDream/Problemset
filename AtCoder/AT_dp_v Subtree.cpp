/**
 * @file    AT_dp_v Subtree.cpp
 * @author  ForgotDream
 * @brief   DP
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
  std::vector<int> fa(n);
  std::function<void(int, int)> dfs1 = [&](int u, int frm) {
    f[u] = 1, fa[u] = frm;
    for (auto v : adj[u]) {
      if (v == frm) { continue; }
      dfs1(v, u);
      (f[u] *= (f[v] + 1)) %= m;
    }
  };

  std::function<void(int, int)> dfs2 = [&](int u, int frm) {
    int pivot = -1;
    for (auto v : adj[u]) {
      if (v == frm) { continue; }
      if (pivot == -1) {
        preVal[v] = 1;
      } else {
        (preVal[v] = preVal[pivot] * (f[pivot] + 1)) %= m;
      }
      pivot = v;
    }
    std::reverse(adj[u].begin(), adj[u].end());
    pivot = -1;
    for (auto v : adj[u]) {
      if (v == frm) { continue; } 
      if (pivot == -1) {
        nxtVal[v] = 1;
      } else {
        (nxtVal[v] = nxtVal[pivot] * (f[pivot] + 1)) %= m;
      }
      pivot = v;
    }
    for (auto v : adj[u]) {
      if (v == frm) { continue; }
      g[v] = ((g[u] + 1) * preVal[v] % m * nxtVal[v]) % m;
    }
    for (auto v : adj[u]) {
      if (v == frm) { continue; }
      dfs2(v, u);
    }
  };

  dfs1(0, -1), dfs2(0, -1);
  for (int i = 0; i < n; i++) {
    std::cout << f[i] * (g[i] + 1) % m << "\n";
  }
  // for (int i = 0; i < n; i++) {
  //   std::cerr << f[i] << " " << g[i] << "\n";
  // }
  // std::cerr << "\n";
  // for (int i = 0; i < n; i++) {
  //   std::cerr << preVal[i] << " " << nxtVal[i] << "\n";
  // }

  return 0;
}
