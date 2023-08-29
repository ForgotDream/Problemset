/**
 * @file    CF1627C Not Assigning.cpp
 * @author  ForgotDream
 * @brief   shabi
 * @date    2023-08-28
 */
#include <algorithm>
#include <iostream>
#include <vector>

using i64 = long long;
using pii = std::pair<int, int>;

constexpr int N = 1e5 + 50;
int n, deg[N];
std::vector<pii> adj[N];
int ans[N];
void dfs(int u, int frm, int cur = 0) {
  for (auto [v, idx] : adj[u]) {
    if (v == frm) continue;
    ans[idx] = cur + 2;
    dfs(v, u, cur ^ 1);
  }
}
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) adj[i].clear(), deg[i] = 0;
  for (int i = 1, u, v; i < n; i++) {
    std::cin >> u >> v;
    adj[u].emplace_back(v, i), adj[v].emplace_back(u, i);
    deg[u]++, deg[v]++;
  }
  if (*std::max_element(deg + 1, deg + n + 1) > 2) {
    std::cout << -1 << "\n";
    return;
  }
  for (int i = 1; i <= n; i++) {
    if (deg[i] == 1) {
      dfs(i, 0);
      break;
    }
  }
  for (int i = 1; i < n; i++) std::cout << ans[i] << " \n"[i == n - 1];
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}