/**
 * @file    AT_abc213_d [ABC213D] Takahashi Tour.cpp
 * @author  ForgotDream
 * @brief   shabi
 * @date    2023-08-27
 */
#include <algorithm>
#include <iostream>
#include <vector>

using i64 = long long;

constexpr int N = 2e5 + 50;
int n;
std::vector<int> adj[N];
int euler[2 * N], clk;
void dfs(int u, int frm) {
  euler[++clk] = u;
  std::sort(adj[u].begin(), adj[u].end());
  for (auto v : adj[u]) {
    if (v == frm) continue;
    dfs(v, u);
    euler[++clk] = u;
  }
}
void solve() {
  std::cin >> n;
  for (int i = 1, u, v; i < n; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
  }
  dfs(1, 0);
  for (int i = 1; i <= clk; i++) std::cout << euler[i] << " \n"[i == clk];
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}