/**
 * @file    CF274B Zero Tree.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-08-15
 */
#include <bits/stdc++.h>
using i64 = long long;
constexpr int N = 1e5 + 50;
int n, a[N];
i64 f[N], g[N];
/* f -> add, g -> sub */
std::vector<int> adj[N];
void dfs(int u, int frm) {
  i64 add = 0, sub = 0;
  for (auto v : adj[u]) {
    if (v == frm) continue;
    dfs(v, u);
    add = std::max(add, f[v]);
    sub = std::max(sub, g[v]);
  }
  f[u] += add, g[u] += sub;
  if (a[u] + add - sub > 0) g[u] += a[u] + add - sub;
  else if (a[u] + add - sub < 0) f[u] -= a[u] + add - sub;
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n;
  for (int i = 1, u, v; i < n; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
  }
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  dfs(1, 0);
  std::cout << f[1] + g[1] << "\n";
  return 0;
}