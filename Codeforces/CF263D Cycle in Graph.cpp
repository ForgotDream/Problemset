/**
 * @file    CF263D Cycle in Graph.cpp
 * @author  ForgotDream
 * @brief   DFS
 * @date    2023-09-02
 */
#include <iostream>
#include <vector>

using i64 = long long;

constexpr int N = 1e5 + 50;
int n, m, k;
std::vector<int> adj[N];
bool vis[N];
int dep[N], fa[N];
void dfs(int u, int frm) {
  vis[u] = true, dep[u] = dep[frm] + 1, fa[u] = frm;
  for (auto v : adj[u]) {
    if (vis[v]) {
      if (dep[u] - dep[v] + 1 >= k + 1) {
        std::cout << dep[u] - dep[v] + 1 << "\n";
        int p = u;
        for (; p != fa[v]; p = fa[p]) std::cout << p << " \n"[p == v];
        exit(0);
      }
      continue;
    }
    dfs(v, u);
  }
}
void solve() {
  std::cin >> n >> m >> k;
  for (int i = 1, u, v; i <= m; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
  }
  dfs(1, 0);
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}