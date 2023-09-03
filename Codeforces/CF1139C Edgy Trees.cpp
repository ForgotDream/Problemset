/**
 * @file    CF1139C Edgy Trees.cpp
 * @author  ForgotDream
 * @brief   DSU
 * @date    2023-08-29
 */
#include <iostream>
#include <numeric>
#include <vector>

using i64 = long long;

namespace DSU {
constexpr int N = 1e5 + 50;
struct Dsu {
  int fa[N], siz[N];
  Dsu() { std::iota(fa, fa + N, 0), std::fill(siz, siz + N, 1); }
  int find(int u) { return u == fa[u] ? u : fa[u] = find(fa[u]); }
  bool merge(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return false;
    fa[u] = v, siz[v] += siz[u];
    return true;
  }
} dsu;
}  // namespace DSU
using namespace DSU;

constexpr int mod = 1e9 + 7;
int n, k;
i64 fastPow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}
void solve() {
  std::cin >> n >> k;
  for (int i = 1, u, v, w; i < n; i++) {
    std::cin >> u >> v >> w;
    if (!w) dsu.merge(u, v);
  }
  i64 ans = fastPow(n, k, mod);
  for (int i = 1; i <= n; i++) {
    if (dsu.fa[i] == i) (ans -= fastPow(dsu.siz[i], k, mod) % mod) %= mod;
  }
  std::cout << (ans + mod) % mod << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}