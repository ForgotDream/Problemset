/*
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2024-02-07
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 21, mod = 998244353;

int n, m, p;
std::vector<int> adj[N];

void solve() {
  std::cin >> n >> m >> p;
  for (int i = 1, u, v; i <= m; i++) {
    std::cin >> u >> v, u--, v--;
    adj[u].push_back(v), adj[v].push_back(u);
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
