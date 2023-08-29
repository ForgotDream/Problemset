/**
 * @file    AT_abc209_d [ABC209D] Collision.cpp
 * @author  ForgotDream
 * @brief   shabi
 * @date    2023-08-27
 */
#include <iostream>
#include <vector>

using i64 = long long;

constexpr int N = 1e5 + 50;
int n, q, dep[N];
std::vector<int> adj[N];
void dfs(int u, int frm) {
  dep[u] = dep[frm] + 1;
  for (auto v : adj[u]) {
    if (v == frm) continue;
    dfs(v, u);
  }
}
void solve() {
  std::cin >> n >> q;
  for (int i = 1, u, v; i < n; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
  }
  dfs(1, 0);
  for (int i = 1, u, v; i <= q; i++) {
    std::cin >> u >> v;
    if ((dep[u] + dep[v]) & 1) std::cout << "Road\n";
    else std::cout << "Town\n";
  }
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}