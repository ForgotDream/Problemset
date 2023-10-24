/**
 * @file    CF412D Giving Awards.cpp
 * @author  ForgotDream
 * @brief   DFS
 * @date    2023-09-02
 */
#include <iostream>
#include <vector>

using i64 = long long;

constexpr int N = 3e4 + 50;
int n, m;
std::vector<int> adj[N];
bool vis[N];
int ans[N], cnt;
void dfs(int u) {
  vis[u] = true;
  for (auto v : adj[u]) {
    if (vis[v]) continue;
    dfs(v);
  }
  ans[++cnt] = u;
}
void solve() {
  std::cin >> n >> m;
  for (int i = 1, u, v; i <= m; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v);
  }
  for (int i = 1; i <= n; i++) {
    if (!vis[i]) dfs(i);
  }
  for (int i = 1; i <= n; i++) std::cout << ans[i] << " \n"[i == n];
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}