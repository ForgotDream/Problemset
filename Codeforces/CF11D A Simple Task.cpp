/**
 * @file    CF11D A Simple Task.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-06-11
 */
#include <bits/stdc++.h>

using i64 = long long;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  std::vector adj(n, std::vector<bool>(n));
  for (int i = 0; i < m; i++) {
    int u, v;
    std::cin >> u >> v;
    u--, v--;
    adj[u][v] = true, adj[v][u] = true;
  }

  std::vector f(1 << n, std::vector<i64>(n));
  i64 ans = 0;
  for (int i = 0; i < n; i++) { f[1 << i][i] = 1; }
  for (int st = 0; st < (1 << n); st++) {
    for (int j = 0; j < n; j++) {
      if (!f[st][j]) { continue; }
      for (int k = 0; k < n; k++) {
        if (!adj[j][k]) { continue; }
        if ((st & -st) > (1 << k)) { continue; } // 我们又见面了，lowbit
        if (st & (1 << k)) {
          if ((1 << k) == (st & -st)) { ans += f[st][j]; }
        } else {
          f[st | (1 << k)][k] += f[st][j];
        }
      }
    }
  }

  std::cout << ((ans - m) >> 1) << "\n";

  return 0;
}