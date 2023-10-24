/**
 * @file    P6145 Timeline G.cpp
 * @author  ForgotDream
 * @brief   Topo Sort
 * @date    2023-05-10
 */
#include <bits/stdc++.h>

using i64 = long long;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int n, m, c;
  std::cin >> n >> m >> c;

  std::vector<int> s(n + 1);
  for (int i = 1; i <= n; i++) {
    std::cin >> s[i];
  }

  std::vector<std::vector<std::pair<int, int>>> g(n + 1);
  std::vector<int> in(n + 1);
  for (int i = 0; i < c; i++) {
    int u, v, w;
    std::cin >> u >> v >> w;
    g[u].emplace_back(v, w);
    in[v]++;
  }

  std::queue<int> q;
  for (int i = 1; i <= n; i++) {
    if (!in[i]) {
      q.push(i);
    }
  }

  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (auto i : g[u]) {
      int v = i.first, w =i.second;
      s[v] = std::max(s[v], s[u] + w);
      if (!--in[v]) {
        q.push(v);
      }
    }
  }

  for (int i = 1; i <= n; i++) {
    std::cout << s[i] << "\n";
  }

  return 0;
}