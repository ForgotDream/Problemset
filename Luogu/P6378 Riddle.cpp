/**
 * @file    P6378 Riddle.cpp
 * @author  ForgotDream
 * @brief   2-SAT
 * @date    2023-05-14
 */
#include <bits/stdc++.h>

using i64 = long long;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m, k;
  std::cin >> n >> m >> k;

  std::vector<std::vector<int>> g(4 * n);
  for (int i = 0; i < m; i++) {
    int u, v;
    std::cin >> u >> v;
    u--, v--;
    g[u + n].push_back(v), g[v + n].push_back(u);
  }

  std::vector pre(n, std::vector<int>(2));
  int p = 2 * n;
  for (int i = 0; i < k; i++) {
    int w;
    std::cin >> w;
    std::vector<int> cur(w);
    for (int i = 0; i < w; i++) {
      std::cin >> cur[i];
      cur[i]--;
    }
    for (int i = 0; i < w; i++) {
      pre[cur[i]][0] = p++;
      pre[cur[i]][1] = p++;
      g[cur[i]].push_back(pre[cur[i]][0]);
      g[pre[cur[i]][1]].push_back(cur[i] + n);
    }
    for (int i = 1; i < w; i++) {
      int u = cur[i - 1], v = cur[i];
      g[pre[u][0]].push_back(v + n);
      g[v].push_back(pre[u][1]);
      g[pre[u][0]].push_back(pre[v][0]);
      g[pre[v][1]].push_back(pre[u][1]);
    }
  }

  std::vector<int> dfn(4 * n), low(4 * n), bln(4 * n);
  std::stack<int> s;
  int clk = 0, cnt = 0;
  std::function<void(int)> tarjan = [&](int u) {
    dfn[u] = low[u] = ++clk;
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

  for (int i = 0; i < p; i++) {
    if (!dfn[i]) {
      tarjan(i);
    }
  }

  for (int i = 0; i < n; i++) {
    if (bln[i] == bln[i + n]) {
      std::cout << "NIE\n";
      return 0;
    }
  }

  std::cout << "TAK\n";

  return 0;
}