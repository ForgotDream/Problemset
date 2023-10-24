/**
 * @file    CF150B Quantity of Strings.cpp
 * @author  ForgotDream
 * @brief   DSU
 * @date    2023-09-05
 */
#include <iostream>
#include <numeric>

using i64 = long long;

constexpr int N = 2050, mod = 1e9 + 7;
int n, m, k;
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
i64 fastPow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}
void solve() {
  std::cin >> n >> m >> k;
  for (int i = 1; i <= n - k + 1; i++) {
    int l = i, r = i + k - 1;
    while (l < r) dsu.merge(l, r), l++, r--;
  }
  int ans = 0;
  for (int i = 1; i <= n; i++) ans += (dsu.fa[i] == i);
  std::cout << fastPow(m, ans, mod) << "\n";  
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}