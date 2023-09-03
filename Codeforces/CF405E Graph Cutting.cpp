/**
 * @file    CF405E Graph Cutting.cpp
 * @author  ForgotDream
 * @brief   DFS
 * @date    2023-09-02
 */
#include <iostream>
#include <vector>

using i64 = long long;

constexpr int N = 1e5 + 50;
int n, m;
std::vector<int> adj[N], f[N];
bool vis[N];
void dfs(int u, int frm) {
  vis[u] = true;
  for (auto v : adj[u]) {
    if (vis[v]) {
      if (v != frm) f[v].push_back(u);
      continue;
    }
    dfs(v, u);
    f[u].push_back(v);
    if (!f[v].empty()) {
      std::cout << f[v][0] << " " << v << " " << u << "\n";
      f[u].pop_back(), f[v].pop_back();
    }
  }
  int siz = f[u].size() - 1;
  while ((siz + 1) > 1) {
    std::cout << f[u][siz] << " " << u << " " << f[u][siz - 1] << "\n";
    siz -= 2;
    f[u].pop_back(), f[u].pop_back();
  }
}
void solve() {
  std::cin >> n >> m;
  for (int i = 1, u, v; i <= m; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
  }
  if (m & 1) {
    std::cout << "No solution\n";
    return;
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