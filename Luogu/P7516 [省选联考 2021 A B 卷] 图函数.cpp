/*
 * @file    P7516 [省选联考 2021 A/B 卷] 图函数.cpp
 * @author  ForgotDream
 * @brief   DP + Floyd
 * @date    2024-02-13
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 1e3 + 50, M = 2e5 + 50;

int n, m;

int adj[N][N], u[M], v[M], g[M], ans[M];

void solve() {
  std::cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    std::cin >> u[i] >> v[i];
    adj[u[i]][v[i]] = i;
  }

  for (int k = n; k >= 1; k--) {
    for (int i = k + 1; i <= n; i++) {
      g[std::min(adj[k][i], adj[i][k])]++;
    }
    for (int i = 1; i <= n; i++) {
      if (!adj[i][k]) continue;
      if (i > k) {
        for (int j = 1; j < k; j++) {
          adj[i][j] = std::max(adj[i][j], std::min(adj[i][k], adj[k][j]));
        }
      } else {
        for (int j = 1; j <= n; j++) {
          adj[i][j] = std::max(adj[i][j], std::min(adj[i][k], adj[k][j]));
        }
      }
    }
  }

  ans[m + 1] = n;
  for (int i = m; i; i--) ans[i] = ans[i + 1] + g[i];
  for (int i = 1; i <= m + 1; i++) std::cout << ans[i] << " \n"[i == m + 1];
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
