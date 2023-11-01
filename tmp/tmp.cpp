/**
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2023-11-01
 */
#include <iostream>
#include <vector>

using i64 = long long;

constexpr int N = 1e6 + 50;
int n, fa[N];
std::vector<int> adj[N];
void dfs(int u) {
  for (auto v : adj[u]) {

  }
}
void solve() {
  std::cin >> n;
  for (int i = 2; i <= n; i++) {
    std::cin >> fa[i];
    adj[fa[i]].push_back(i);
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
