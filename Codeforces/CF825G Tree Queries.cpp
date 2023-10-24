/**
 * @file    CF825G Tree Queries.cpp
 * @author  ForgotDream
 * @brief   DFS
 * @date    2023-08-11
 */
#include <bits/stdc++.h>
using i64 = long long;
constexpr int N = 1e6 + 50;
int n, q, lst, ans = 1e9;
int min[N];
std::vector<int> adj[N];
void dfs(int u, int frm) {
  min[u] = std::min(u, min[frm]);
  for (auto v : adj[u]) {
    if (v == frm) continue;
    dfs(v, u);
  }
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n >> q;
  for (int i = 1, u, v; i < n; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
  }
  for (int i = 1; i <= q; i++) {
    int opt, u;
    std::cin >> opt >> u;
    u = (lst + u) % n + 1;
    if (opt == 1) {
      if (i == 1) min[0] = 1e9, dfs(u, 0);
      ans = std::min(ans, min[u]);
    } else {
      std::cout << (lst = std::min(ans, min[u])) << "\n";
    }
  }
  return 0;
}