/**
 * @file    CF813C The Tag Game.cpp
 * @author  ForgotDream
 * @brief   DFS
 * @date    2023-09-05
 */
#include <cstring>
#include <iostream>
#include <vector>

using i64 = long long;

constexpr int N = 2e5 + 50;
int n, x;
std::vector<int> adj[N];
int dep[N], fa[N], max[N];
void dfs(int u, int frm) {
  dep[u] = dep[frm] + 1, fa[u] = frm;
  for (auto v : adj[u]) {
    if (v == frm) continue;
    dfs(v, u);
    max[u] = std::max(max[u], max[v] + 1);
  }
}
void solve() {
  std::cin >> n >> x;
  for (int i = 1, u, v; i < n; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
  }
  dfs(1, 0);
  int ans = dep[x] - dep[1], p = x;
  while (p) {
    if (dep[x] - dep[p] >= dep[p] - dep[1]) break;
    ans = std::max(ans, 2 * (dep[p] - dep[1] + max[p]));
    p = fa[p];
  }
  std::cout << ans << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}