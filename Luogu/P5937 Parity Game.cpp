/**
 * @file    P5937 Parity Game.cpp
 * @author  ForgotDream
 * @brief   DSU
 * @date    2023-05-07
 */
#include <bits/stdc++.h>

using i64 = long long;
using i64u = unsigned long long;
using f80 = long double;

struct DSU {
  int n;
  std::vector<int> fa;

  DSU(int _n) : n(_n) {
    fa.resize(n);
    std::iota(fa.begin(), fa.end(), 0);
    return;
  }

  int find(int u) {
    return u == fa[u] ? u : fa[u] = find(fa[u]);
  }

  bool merge(int u, int v) {
    int fau = find(u), fav = find(v);
    if (fau == fav) {
      return false;
    }
    fa[fau] = fav;
    return true;
  }

};

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  std::vector<std::tuple<int, int, std::string>> a;
  std::vector<int> b;
  for (int i = 0; i < m; i++) {
    int l, r;
    std::string s;
    std::cin >> l >> r >> s;
    a.emplace_back(l, r, s);
    b.push_back(l), b.push_back(r);
  }

  std::sort(b.begin(), b.end());
  b.erase(std::unique(b.begin(), b.end()), b.end());
  DSU dsu(2 * b.size() + 1);

  for (int i = 0; i < m; i++) {
    std::get<0>(a[i]) = std::lower_bound(b.begin(), b.end(), std::get<0>(a[i]) - 1) - b.begin();
    std::get<1>(a[i]) = std::lower_bound(b.begin(), b.end(), std::get<1>(a[i])) - b.begin();
  }

  for (int i = 0; i < m; i++) {
    if (std::get<2>(a[i]) == "even") {
      if (dsu.find(std::get<0>(a[i])) == dsu.find(std::get<1>(a[i])) + b.size() ||
          dsu.find(std::get<1>(a[i])) == dsu.find(std::get<0>(a[i])) + b.size()) {
        std::cout << i << "\n";
        return 0;
      }
      dsu.merge(std::get<0>(a[i]), std::get<1>(a[i]));
      dsu.merge(std::get<0>(a[i]) + b.size(), std::get<1>(a[i]) + b.size());
    } else {
      if (dsu.find(std::get<0>(a[i])) + b.size() == dsu.find(std::get<1>(a[i])) + b.size() ||
          dsu.find(std::get<1>(a[i])) == dsu.find(std::get<0>(a[i]))) {
        std::cout << i << "\n";
        return 0;
      }
      dsu.merge(std::get<0>(a[i]), std::get<1>(a[i]) + b.size());
      dsu.merge(std::get<0>(a[i]) + b.size(), std::get<1>(a[i]));
    }
  }

  std::cout << m << "\n";

  return 0;
}