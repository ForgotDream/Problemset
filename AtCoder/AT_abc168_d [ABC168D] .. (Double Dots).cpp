/**
 * @file    AT_abc168_d [ABC168D] .. (Double Dots).cpp
 * @author  ForgotDream
 * @brief   BFS
 * @date    2023-08-27
 */
#include <iostream>
#include <queue>
#include <vector>

using i64 = long long;

constexpr int N = 2e5 + 50;
int n, m;
std::vector<int> adj[N];
int dis[N], ans[N];
void bfs() {
  std::queue<int> q;
  q.push(1), dis[1] = 1;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (auto v : adj[u]) {
      if (dis[v]) continue;
      dis[v] = dis[u] + 1, q.push(v);
    }
  }
}
void solve() {
  std::cin >> n >> m;
  for (int i = 1, u, v; i <= m; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
  }
  bfs();
  for (int u = 1; u <= n; u++) {
    for (auto v : adj[u]) {
      if (dis[v] == dis[u] + 1 && !ans[v]) ans[v] = u;
    }
  }
  std::cout << "Yes\n";
  for (int i = 2; i <= n; i++) std::cout << ans[i] << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}