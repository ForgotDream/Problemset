/**
 * @file    P1955 程序自动分析.cpp
 * @author  ForgotDream
 * @brief   DSU
 * @date    2023-06-06
 */
#include <bits/stdc++.h>

using i64 = long long;

struct Constraint { int u, v, opt; };
struct DSU {
  int n;
  std::vector<int> fa;
  DSU(int _n) {
    n = _n;
    fa.resize(n);
    std::iota(fa.begin(), fa.end(), 0);
  }
  int find(int u) {
    while (u != fa[u]) { u = fa[u] = fa[fa[u]]; }
    return u;
  }
  bool merge(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) { return false; }
    fa[u] = v;
    return true;
  }
};

void solve() {
  int n;
  std::cin >> n;

  std::vector<Constraint> query(n);
  std::vector<int> a;
  for (int i = 0; i < n; i++) {
    std::cin >> query[i].u >> query[i].v >> query[i].opt;
    a.push_back(query[i].u); 
    a.push_back(query[i].v);
  }

  std::sort(a.begin(), a.end());
  a.erase(std::unique(a.begin(), a.end()), a.end());

  for (int i = 0; i < n; i++) {
    query[i].u = std::lower_bound(a.begin(), a.end(), query[i].u) - a.begin();
    query[i].v = std::lower_bound(a.begin(), a.end(), query[i].v) - a.begin();
  }

  std::sort(query.begin(), query.end(), [](Constraint lhs, Constraint rhs) {
    return lhs.opt > rhs.opt;
  });

  int m = a.size();
  DSU dsu(m);
  for (int i = 0; i < n; i++) {
    int u = query[i].u, v = query[i].v, opt = query[i].opt;
    if (opt == 1) {
      dsu.merge(u, v);
    } else if (dsu.find(u) == dsu.find(v)) {
      std::cout << "NO\n";
      return;
    }
  }
  std::cout << "YES\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  std::cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}