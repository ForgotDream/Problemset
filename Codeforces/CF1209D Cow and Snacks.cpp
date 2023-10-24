/**
 * @file    CF1209D Cow and Snacks.cpp
 * @author  ForgotDream
 * @brief   DSU
 * @date    2023-09-02
 */
#include <iostream>

using i64 = long long;

constexpr int N = 1e5 + 50;
int n, k, fa[N];
int find(int u) { return u == fa[u] ? u : fa[u] = find(fa[u]); }
bool merge(int u, int v) {
  u = find(u), v = find(v);
  if (u == v) return false;
  fa[u] = v;
  return true;
}
void solve() {
  std::cin >> n >> k;
  for (int i = 1; i <= n; i++) fa[i] = i;
  int ans = 0;
  for (int i = 1, u, v; i <= k; i++) {
    std::cin >> u >> v;
    if (!merge(u, v)) ans++;
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