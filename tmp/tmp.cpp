/**
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2023-05-15
 */
#include <bits/stdc++.h>

using i64 = long long;

struct Edge {
  int u, v;
  bool deleted;
  Edge(int _u, int _v) { u = _u, v = _v, deleted = false; }
  void del() { deleted = true; }
};

void solve() {
  int n;
  std::cin >> n;

  std::vector<Edge> edges;
  std::vector<std::vector<int>> g(26);
  for (int i = 0; i < n; i++) {
    std::string s;
    std::cin >> s;
    int u = *s.begin() - 'a', v = *s.rbegin() - 'a';
    edges.emplace_back(u, v);
    g[u].push_back(edges.size() - 1);
  }

  std::vector<int> cur(26);
  std::function<void(int)> dfs = [&](int u) {
    for (int &i = cur[u]; i < g[u].size(); i++) {
      
    }
  };
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  std::cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}