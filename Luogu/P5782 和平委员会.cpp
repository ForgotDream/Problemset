/**
 * @file    P5782 和平委员会.cpp
 * @author  ForgotDream
 * @brief   2-SAT
 * @date    2023-05-14
 */
#include <bits/stdc++.h>

using i64 = long long;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  auto convert = [](int u) {
    return (u % 2 == 0 ? u - 1 : u + 1); 
  };

  std::vector<std::vector<int>> g(2 * n + 1);
  for (int i = 0; i < m; i++) {
    int u, v;
    std::cin >> u >> v;
    g[u].push_back(convert(v));
    g[v].push_back(convert(u));
  }

  std::vector<int> dfn(2 * n + 1), low(2 * n + 1), bln(2 * n + 1);
  std::stack<int> s;
  int clk = 0, cnt = 0;
  std::function<void(int)> tarjan = [&](int u) {
    low[u] = dfn[u] = ++clk;
    s.push(u);
    for (auto v : g[u]) {
      if (!dfn[v]) {
        tarjan(v);
        low[u] = std::min(low[u], low[v]);
      } else if (!bln[v]) {
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

  for (int i = 1; i <= 2 * n; i++) {
    if (!dfn[i]) {
      tarjan(i);
    }
  }

  for (int i = 1; i <= 2 * n; i += 2) {
    if (bln[i] == bln[i + 1]) {
      std::cout << "NIE\n";
      return 0;
    } 
  }

  for (int i = 1; i <= 2 * n; i += 2) {
    if (bln[i] < bln[i + 1]) {
      std::cout << i << "\n";
    } else {
      std::cout << i + 1 << "\n";
    }
  }

  return 0;
}