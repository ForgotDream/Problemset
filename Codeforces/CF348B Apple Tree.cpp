/**
 * @file    CF348B Apple Tree.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-08-21
 */
#include <iostream>
#include <numeric>
#include <vector>

using i64 = long long;

constexpr int N = 1e5 + 50;
constexpr i64 inf = 1e18;
int n;
i64 a[N];
std::vector<int> adj[N];
i64 ans, m = 1, l = inf;

void dfs(int u, int frm, i64 d) {
  m = std::lcm(m, d);
  if (d > ans || d < 0) {
    std::cout << ans << "\n";
    exit(0);
  }
  if (u != 1 && adj[u].size() == 1) l = std::min(l, a[u] * d);
  for (auto v : adj[u]) {
    if (v == frm) continue;
    dfs(v, u, d * (adj[u].size() - (u != 1)));
  }
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i], ans += a[i];
  for (int i = 1, u, v; i < n; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  dfs(1, 0, 1);
  std::cout << ans - l / m * m << "\n";

  return 0;
}