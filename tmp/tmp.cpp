/**
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2023-11-27
 */
#include <bits/stdc++.h>

using i64 = int64_t;
using pil = std::pair<int, i64>;

constexpr int N = 2e5 + 50;
int n, fa[N];
i64 t;
std::vector<pil> adj[N];
i64 dis[N];
void dfs(int u) {
  for (auto [v, w] : adj[u]) {
    dis[v] = dis[u] + w, dfs(v);
  }
}
void solve() {
  std::cin >> n >> t;
  for (int i = 2; i <= n; i++) {
    i64 w;
    std::cin >> fa[i] >> w, adj[fa[i]].emplace_back(i, w);
  }
  dfs(1);
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
