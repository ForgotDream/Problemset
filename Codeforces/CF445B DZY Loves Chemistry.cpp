/**
 * @file    CF445B DZY Loves Chemistry.cpp
 * @author  ForgotDream
 * @brief   DSU
 * @date    2023-08-28
 */
#include <iostream>
#include <numeric>

using i64 = long long;

namespace DSU {
constexpr int N = 55;
struct DSU {
  int fa[N];
  DSU() { std::iota(fa, fa + N, 0); }
  int find(int u) { return u == fa[u] ? u : fa[u] = find(fa[u]); }
  bool merge(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return false;
    fa[u] = v;
    return true;
  }
} dsu;
}
int n, m;
void solve() {
  std::cin >> n >> m;
  for (int i = 1, u, v; i <= m; i++) {
    std::cin >> u >> v;
    DSU::dsu.merge(u, v);
  }
  i64 ans = 1ll << n;
  for (int i = 1; i <= n; i++) {
    if (DSU::dsu.fa[i] == i) ans >>= 1, std::cerr << i << "\n";
  }
  std::cout << ans << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}