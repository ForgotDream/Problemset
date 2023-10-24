/**
 * @file    CF28B pSort.cpp
 * @author  ForgotDream
 * @brief   DSU
 * @date    2023-09-05
 */
#include <iostream>
#include <numeric>

using i64 = long long;

constexpr int N = 105;
int n, p[N], d[N];
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
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> p[i];
  for (int i = 1; i <= n; i++) std::cin >> d[i];
  for (int i = 1; i <= n; i++) {
    if (i + d[i] <= n) dsu.merge(i, i + d[i]);
    if (i - d[i] >= 1) dsu.merge(i, i - d[i]);
  }
  for (int i = 1; i <= n; i++) {
    if (dsu.find(p[i]) != dsu.find(i)) {
      std::cout << "NO\n";
      return;
    }
  }
  std::cout << "YES\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}