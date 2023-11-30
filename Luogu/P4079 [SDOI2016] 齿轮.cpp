/**
 * @file    P4079 [SDOI2016] 齿轮.cpp
 * @author  ForgotDream
 * @brief   DSU
 * @date    2023-11-29
 */
#include <bits/stdc++.h>

using i64 = int64_t;
using f96 = long double;

constexpr int N = 1050;
int n, m;
struct DSU {
  int fa[N];
  f96 val[N];
  DSU() { clear(); }
  void clear() {
    std::iota(fa, fa + N, 0);
    std::fill(val, val + N, 1);
  }
  int find(int u) {
    if (u == fa[u]) return u;
    int p = find(fa[u]);
    val[u] *= val[fa[u]];
    return fa[u] = p;
  }
  bool merge(int u, int v, f96 w) {
    int fau = find(u), fav = find(v);
    if (fau == fav) return false;
    fa[fav] = fau, val[fav] *= val[u] / val[v] * w;
    return true;
  }
} dsu;
void solve() {
  static int t = 0;
  std::cin >> n >> m;
  bool flg = true;
  dsu.clear();
  for (int i = 1, u, v; i <= m; i++) {
    f96 x, y;
    std::cin >> u >> v >> x >> y;
    if (!dsu.merge(u, v, y / x)) {
      // if (x / y != dsu.val[u] / dsu.val[v]) flg = false;
      if (std::abs(x * dsu.val[v] - dsu.val[u] * y) > 1e-12) flg = false;
      // std::cout << x / y << " " << dsu.val[u] / dsu.val[v] << "\n";
    }
  }
  std::cout << "Case #" << ++t << ": " << (flg ? "Yes\n" : "No\n");
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}
