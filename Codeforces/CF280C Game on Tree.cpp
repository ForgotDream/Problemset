/**
 * @file    CF280C Game on Tree.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-08-16
 */
#include <bits/stdc++.h>

using i64 = long long;
using f80 = long double;

constexpr int N = 1e5 + 50;
int n;
std::vector<int> adj[N];
int dep[N];
f80 ans;

void dfs(int u, int frm) {
  dep[u] = dep[frm] + 1;
  for (auto v : adj[u]) {
    if (v == frm) continue;
    dfs(v, u);
  }
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout << std::fixed << std::setprecision(20);

  std::cin >> n;
  for (int i = 1, u, v; i < n; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
  }

  dfs(1, 0);
  for (int i = 1; i <= n; i++) ans += 1. / dep[i];
  std::cout << ans << "\n";

  return 0;
}