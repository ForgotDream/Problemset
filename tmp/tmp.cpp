/**
 * @file    
 * @author  ForgotDream
 * @brief   
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

  DSU dsu(n + 1);
  for (int i = 0; i < m; i++) {
    int l, r;
    std::string s;
    std::cin >> l >> r >> s;
  }

  return 0;
}