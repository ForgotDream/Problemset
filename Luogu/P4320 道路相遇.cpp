/**
 * @file    P4320 道路相遇.cpp
 * @author  ForgotDream
 * @brief   圆方树
 * @date    2023-05-11
 */
#include <bits/stdc++.h>

using i64 = long long;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<int>> g(n + 1), t(2 * n + 1);
  for (int i = 0; i < m; i++) {
    int u, v;
    std::cin >> u >> v;
    g[u].push_back(v), g[v].push_back(u);
  }

  std::vector<int> dfn(n + 1), low(n + 1);
  int clk = 0, cnt = n;
  std::stack<int> s;
  std::function<void(int)> tarjan = [&](int u) {
    dfn[u] = low[u] = ++clk;
    s.push(u);
    for (auto v : g[u]) {
      if (!dfn[v]) {
        tarjan(v);
        low[u] = std::min(low[u], low[v]);
        if (low[v] == dfn[u]) {
          int p;
          ++cnt;
          do {
            p = s.top();
            s.pop();
            t[p].push_back(cnt), t[cnt].push_back(p);
          } while (p != v);
          t[u].push_back(cnt), t[cnt].push_back(u);
        }
      } else {
        low[u] = std::min(low[u], dfn[v]);
      }
    }
  };

  tarjan(1);

  std::vector<int> dep(cnt + 1);
  std::vector fa(cnt + 1, std::vector<int>(20));
  std::function<void(int, int)> dfs = [&](int u, int frm) {
    dep[u] = dep[frm] + 1;
    fa[u][0] = frm;
    for (int i = 1; i <= 19; i++) {
      fa[u][i] = fa[fa[u][i - 1]][i - 1];
    }
    for (auto v : t[u]) {
      if (v == frm) {
        continue;
      }
      dfs(v, u);
    }
  };

  std::function<int(int, int)> getLCA = [&](int u, int v) -> int {
    if (dep[u] < dep[v]) {
      std::swap(u, v);
    }
    for (int i = 19; i >= 0; i--) {
      if (dep[fa[u][i]] >= dep[v]) {
        u = fa[u][i];
      }
    }
    if (u == v) {
      return u;
    }
    for (int i = 19; i >= 0; i--) {
      if (fa[u][i] != fa[v][i]) {
        u = fa[u][i], v = fa[v][i];
      }
    }
    return fa[u][0];
  };

  dfs(1, 0);

  int q;
  std::cin >> q;
  
  while (q--) {
    int u, v;
    std::cin >> u >> v;
    int lca = getLCA(u, v);
    int d = dep[u] + dep[v] - 2 * dep[lca];
    std::cout << d / 2 + 1 << "\n";
  }

  return 0;
}