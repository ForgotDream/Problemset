/**
 * @file    CF780E Underground Lab.cpp
 * @author  ForgotDream
 * @brief   图论 + 欧拉序
 * @date    2023-08-24
 */
#include <iostream>
#include <vector>

using i64 = long long;

constexpr int N = 4e5 + 50;
int n, m, k;
std::vector<int> adj[N];
bool vis[N];
int cnt, p[N];
void dfs(int u) {
  vis[u] = true, p[++cnt] = u;
  for (auto v : adj[u]) {
    if (vis[v]) continue;
    dfs(v), p[++cnt] = u;
  }
}
void solve() {
  std::cin >> n >> m >> k;
  for (int i = 1, u, v; i <= m; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
  }
  dfs(1);
  for (int i = 1; i <= k; i++) {
    int cur = std::min(cnt, (2 * n - 1) / k + 1);
    if (!cur) {
      std::cout << "1 1\n";
      continue;
    }
    std::cout << cur << " ";
    for (int j = 1; j <= cur; j++) std::cout << p[cnt--] << " \n"[j == cur];
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