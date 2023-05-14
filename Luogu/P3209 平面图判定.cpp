/**
 * @file    P3209 平面图判定.cpp
 * @author  ForgotDream
 * @brief   2-SAT
 * @date    2023-05-14
 */
#include <bits/stdc++.h>

using i64 = long long;

void solve() {
  int n, m;
  std::cin >> n >> m;

  std::vector<std::pair<int, int>> edges(m);
  std::vector<bool> invalid(m);
  for (int i = 0; i < m; i++) {
    std::cin >> edges[i].first >> edges[i].second;
  }

  std::vector<int> circle(n), idx(n + 1);
  for (int i = 0; i < n; i++) {
    std::cin >> circle[i];
    idx[circle[i]] = i;
  }

  if (m > 3 * n - 6) {
    std::cout << "NO\n";
    return;
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      int u = edges[j].first, v = edges[j].second;
      if ((u == circle[i] && v == circle[(i + 1) % n]) || 
          (v == circle[i] && u == circle[(i + 1) % n])) {
        invalid[j] = true;
      }
    }
  }

  std::vector<std::vector<int>> g(2 * m);
  for (int i = 0; i < m; i++) {
    if (invalid[i]) {
      continue;
    }
    for (int j = i + 1; j < m; j++) {
      if (invalid[j]) {
        continue;
      }
      int u1 = idx[edges[i].first], v1 = idx[edges[i].second];
      int u2 = idx[edges[j].first], v2 = idx[edges[j].second];
      if (u1 > v1) {
        std::swap(u1, v1);
      }
      if (u2 > v2) {
        std::swap(u2, v2);
      }
      if ((u1 < u2 && u2 < v1 && v1 < v2) ||
          (u2 < u1 && u1 < v2 && v2 < v1)) {
        g[i].push_back(j + m), g[j].push_back(i + m);
        g[i + m].push_back(j), g[j + m].push_back(i);
      }
    }
  }

  std::vector<int> dfn(2 * m), low(2 * m), bln(2 * m);
  std::stack<int> s;
  int clk = 0, cnt = 0;
  std::function<void(int)> tarjan = [&](int u) {
    dfn[u] = low[u] = ++clk;
    s.push(u);
    for (auto v : g[u]) {
      if (!dfn[v]) {
        tarjan(v);
        low[u] = std::min(low[u], low[v]);
      } else {
        low[u] = std::min(low[u], dfn[v]);
      }
    }
    if (dfn[u] == low[u]) {
      int p;
      ++cnt;
      do {
        p = s.top();
        s.pop();
        bln[p] = cnt;
      } while (p != u);
    }
  };

  for (int i = 0; i < 2 * m; i++) {
    if (!dfn[i]) {
      tarjan(i);
    }
  }

  for (int i = 0; i < m; i++) {
    if (bln[i] == bln[i + m]) {
      std::cout << "NO\n";
      return;
    }
  }

  std::cout << "YES\n";
  return;
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