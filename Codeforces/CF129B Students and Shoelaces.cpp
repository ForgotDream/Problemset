/**
 * @file    CF129B Students and Shoelaces.cpp
 * @author  ForgotDream
 * @brief   shabi
 * @date    2023-08-28
 */
#include <iostream>
#include <queue>
#include <vector>

using i64 = long long;

constexpr int N = 105;
int n, m;
std::vector<int> adj[N];
int deg[N];
void solve() {
  std::cin >> n >> m;
  for (int i = 1, u, v; i <= m; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
    deg[u]++, deg[v]++;
  }
  std::queue<int> q;
  int ans = 0;
  while (true) {
    while (!q.empty()) q.pop();
    for (int i = 1; i <= n; i++) {
      if (deg[i] == 1) q.push(i), deg[i] = 0;
    }
    if (q.empty()) break;
    ans++;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (auto v : adj[u]) {
        if (deg[v]) deg[v]--;
      }
    }
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