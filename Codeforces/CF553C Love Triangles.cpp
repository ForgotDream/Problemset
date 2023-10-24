/**
 * @file    CF553C Love Triangles.cpp
 * @author  ForgotDream
 * @brief   DSU + Math
 * @date    2023-09-03
 */
#include <iostream>
#include <numeric>
#include <vector>

using i64 = long long;

constexpr int N = 1e5 + 50, mod = 1e9 + 7;
int n, m;
std::vector<int> adj[N];
int fa[N], d[N];
int find(int u) {
  if (u == fa[u]) return u;
  int res = find(fa[u]);
  d[u] ^= d[fa[u]];
  return fa[u] = res;
}
i64 fastPow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}
void solve() {
  std::cin >> n >> m;
  std::iota(fa + 1, fa + n + 1, 1);
  for (int i = 1, u, v, w; i <= m; i++) {
    std::cin >> u >> v >> w;
    int fau = find(u), fav = find(v);
    if (fau == fav) {
      if ((w && d[u] != d[v]) || (!w && d[u] == d[v])) {
        std::cout << 0 << "\n";
        return;
      }
    } else {
      d[fau] = (!w) ^ d[u] ^ d[v];
      fa[fau] = fav;
    }
  }
  int cnt = 0;
  for (int i = 1; i <= n; i++) cnt += (fa[i] == i);
  std::cout << fastPow(2, cnt - 1, mod) << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}