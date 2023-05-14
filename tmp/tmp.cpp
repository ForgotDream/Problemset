/**
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2023-05-14
 */
#include <bits/stdc++.h>

using i64 = long long;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<int>> g(2 * n);
  for (int i = 0; i < m; i++) {
    int u, v;
    std::cin >> u >> v;
    u--, v--;
    g[u].push_back(v ^ 1);
    g[v].push_back(u ^ 1);
  }

  std::vector<int> dfn(2 * n), low(2 * n), bln(2 * n);
  std::stack<int> s;
  int clk = 0, cnt = 0;
  std::function<void(int)> tarjan = [&](int u) {
    low[u] = dfn[u] = ++clk;
    s.push(u);
    for (auto v : g[u]) {
      if (!dfn[v]) {
        tarjan(v);
        low[u] = std::min(low[u], low[v]);
      } else {
        low[u] = std::min(low[u], dfn[v]);
      }
    }
    if (low[u] == dfn[u]) {
      int p;
      ++cnt;
      do {
        p = s.top();
        s.pop();
        bln[p] = cnt;
      } while (p != u);
    }
  };

  for (int i = 0; i < 2 * n; i++) {
    if (!dfn[i]) {
      tarjan(i);
    }
  }

  for (int i = 0; i < n; i++) {
    if (bln[2 * i] == bln[2 * i + 1]) {
      std::cout << "NIE\n";
      return 0;
    } 
  }

  for (int i = 0; i < n; i++) {
    if (bln[2 * i] < bln[2 * i + 1]) {
      std::cout << 2 * i + 1 << "\n";
    } else {
      std::cout << 2 * i + 2 << "\n";
    }
  }

  return 0;
}