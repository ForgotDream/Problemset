/*
 * @file    P6383 『MdOI R2』Resurrection.cpp
 * @author  ForgotDream
 * @brief   DP on Tree
 * @date    2024-01-05
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 3050, mod = 998244353;
int n;
std::vector<int> adj[N];

i64 f[N][N];
void dfs(int u, int frm) {
  std::fill(f[u] + 1, f[u] + n + 1, 1);
  for (auto v : adj[u]) {
    if (v == frm) continue;
    dfs(v, u);
    for (int i = 1; i <= n; i++) (f[u][i] *= f[v][i + 1]) %= mod;
  }
  for (int i = 2; i <= n + 1; i++) (f[u][i] += f[u][i - 1]) %= mod;
}

void solve() {
  std::cin >> n;
  for (int i = 1, u, v; i < n; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
  }
  dfs(n, 0);
  i64 ans = 1;
  for (auto v : adj[n]) (ans *= f[v][1]) %= mod;
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
