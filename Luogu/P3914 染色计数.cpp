/*
 * @file    P3914 染色计数.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2024-01-29
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 5050, mod = 1e9 + 7;

int n, m;
bool col[N][N];
std::vector<int> adj[N];

int f[N][N], s[N];

void dfs(int u, int frm) {
  for (int i = 1; i <= m; i++) if (col[u][i]) f[u][i] = 1;
  for (auto v : adj[u]) {
    if (v == frm) continue;
    dfs(v, u);
    for (int i = 1; i <= m; i++) {
      if (!col[u][i]) continue;
      f[u][i] = 1ll * f[u][i] * (s[v] - f[v][i] + mod) % mod;
    }
  }
  for (int i = 1; i <= m; i++) if (col[u][i]) (s[u] += f[u][i]) %= mod;
}

void solve() {
  std::cin >> n >> m;
  for (int i = 1, ct; i <= n; i++) {
    std::cin >> ct;
    for (int u; ct; ct--) std::cin >> u, col[i][u] = true;
  }
  for (int i = 1, u, v; i < n; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
  }

  dfs(1, 0);
  std::cout << s[1] << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
