/*
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2024-02-21
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;
using pll = std::pair<i64, i64>;

constexpr int N = 10050;

int n, m, l, s, t;
std::vector<pll> adj[N];

void solve() {
  std::cin >> n >> m >> l >> s >> t, s++, t++;
  for (int i = 1, u, v, w; i <= m; i++) {
    std::cin >> u >> v >> w, u++, v++;
    adj[u].emplace_back(v, w), adj[v].emplace_back(u, w);
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  std::cin >> t;
  while (t--) solve();

  return 0;
}
