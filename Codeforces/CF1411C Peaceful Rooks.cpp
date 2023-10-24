/**
 * @file    CF1411C Peaceful Rooks.cpp
 * @author  ForgotDream
 * @brief   DSU
 * @date    2023-09-02
 */
#include <iostream>
#include <numeric>

using i64 = long long;

constexpr int N = 1e5 + 50;
struct DSU {
  int fa[N];
  DSU() { init(); }
  void init() { std::iota(fa, fa + N, 0); }
  int find(int u) { return u == fa[u] ? u : fa[u] = find(fa[u]); }
  bool merge(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return false;
    fa[u] = v;
    return true;
  }
} dsu;
int n, m;
void solve() {
  dsu.init();
  std::cin >> n >> m;
  int ans = m;
  for (int i = 1, x, y; i <= m; i++) {
    std::cin >> x >> y;
    if (x == y) {
      ans--;
      continue;
    }
    if (!dsu.merge(x, y)) ans++;
  }
  std::cout << ans << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}