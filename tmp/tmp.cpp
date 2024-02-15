/*
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2024-02-14
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 5050;

int n;
bool typ[N];
std::vector<int> adj[N];

void dfs(int u, int frm) {
  for (auto v : adj[u]) {
    if (v == frm) continue;
    dfs(v, u);
  }
}

void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) {
    char c;
    std::cin >> c;
    typ[i] = c - '0';
  }
  for (int i = 1, u, v; i < n; i++) {
    std::cin >> u >> v;
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
