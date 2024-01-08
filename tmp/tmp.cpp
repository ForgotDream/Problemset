/*
 * @file
 * @author  ForgotDream
 * @brief
 * @date    2024-01-08
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 50;
int n;
std::vector<int> adj[N];

void solve() {
  std::cin >> n;
  for (int i = 1, u, v; i <= n; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
  }
  for (int i = 1; i <= n; i++) {
    
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
