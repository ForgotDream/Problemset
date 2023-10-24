/**
 * @file    CF103B Cthulhu.cpp
 * @author  ForgotDream
 * @brief   DFS
 * @date    2023-09-02
 */
#include <iostream>
#include <vector>

using i64 = long long;

const int N = 105;
int n, m;
std::vector<int> adj[N];
int cnt;
bool vis[N];
void dfs(int u, int frm) {
  vis[u] = true;
  for (auto v : adj[u]) {
    if (vis[v]) {
      if (v != frm) cnt++;
      if (cnt > 2) {
        std::cout << "NO\n";
        exit(0);
      }
      continue;
    }
    dfs(v, u);
  }
}
void solve() {
  std::cin >> n >> m;
  for (int i = 1, u, v; i <= m; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
  }
  dfs(1, 0);
  if (cnt == 0) {
    std::cout << "NO\n";
    return;
  }
  for (int i = 1; i <= n; i++) {
    if (!vis[i]) {
      std::cout << "NO\n";
      return;
    }
  }
  std::cout << "FHTAGN!\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}