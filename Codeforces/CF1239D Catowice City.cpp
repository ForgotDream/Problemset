/**
 * @file    CF1239D Catowice City.cpp
 * @author  ForgotDream
 * @brief   SCC
 * @date    2023-06-05
 */
#include <bits/stdc++.h>

using i64 = long long;

void solve() {
  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<int>> adj(n);
  for (int i = 0; i < m; i++) {
    int u, v;
    std::cin >> u >> v;
    if (u == v) {
      continue;
    }
    u--, v--;
    adj[u].push_back(v);
  }

  std::vector<int> dfn(n), low(n), bln(n), siz(1);
  std::vector<bool> instk(n);
  std::stack<int> s;
  int clk = 0, cnt = 0;
  std::function<void(int)> tarjan = [&](int u) {
    dfn[u] = low[u] = ++clk;
    s.push(u), instk[u] = true;
    for (auto v : adj[u]) {
      if (!dfn[v]) {
        tarjan(v);
        low[u] = std::min(low[u], low[v]);
      } else if (instk[v]) {
        low[u] = std::min(low[u], dfn[v]);
      }
    }
    if (dfn[u] == low[u]) {
      cnt++;
      siz.emplace_back(0);
      int p;
      do {
        p = s.top(), s.pop(), instk[p] = false;
        bln[p] = cnt;
        siz[cnt]++;
      } while (p != u);
    }
  };

  for (int i = 0; i < n; i++) {
    if (!dfn[i]) {
      tarjan(i);
    }
  }

  if (cnt == 1) {
    std::cout << "No\n";
    return;
  }

  std::cout << "Yes\n" << siz[1] << " " << n - siz[1] << "\n";
  for (int i = 0; i < n; i++) {
    if (bln[i] == 1) {
      std::cout << i + 1 << " ";
    }
  }
  std::cout << "\n";
  for (int i = 0; i < n; i++) {
    if (bln[i] != 1) {
      std::cout << i + 1 << " ";
    }
  }
  std::cout << "\n";
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
