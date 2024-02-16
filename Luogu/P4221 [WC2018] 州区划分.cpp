/*
 * @file    P4221 [WC2018] 州区划分.cpp
 * @author  ForgotDream
 * @brief   FWT / FMT + DP
 * @date    2024-02-15
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 21, M = 405;
constexpr int mod = 998244353;

int n, m, p, w[N], U[M], V[M];

int deg[N];

i64 f[N + 1][1 << N], g[N + 1][1 << N], inv[1 << N];

struct DSU {
  int fa[N];

  void init(int _n) { std::iota(fa, fa + _n, 0); }

  int find(int u) { return u == fa[u] ? u : fa[u] = find(fa[u]); }

  bool merge(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return false;
    fa[u] = v;
    return true;
  }
} dsu;

inline i64 fast_pow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}

void fwt(i64 *a, int len, int opt) {
  for (int h = 2; h <= len; h <<= 1) {
    for (i64 *j = a; j < a + len; j += h) {
      for (i64 *k = j; k < j + (h >> 1); k++) {
        if (opt == 1) k[h >> 1] = (k[h >> 1] + k[0]) % mod;
        else k[h >> 1] = (k[h >> 1] - k[0] + mod) % mod;
      }
    }
  }
}

inline int popcnt(int u) { return __builtin_popcount(u); }

void solve() {
  std::cin >> n >> m >> p;
  for (int i = 0; i < m; i++) std::cin >> U[i] >> V[i], U[i]--, V[i]--;
  for (int i = 0; i < n; i++) std::cin >> w[i];

  int mask = 1 << n;
  for (int st = 0; st < mask; st++) {
    dsu.init(n);
    std::fill(deg, deg + n, 0);

    i64 cur = 0;
    for (int i = 0; i < n; i++) if (st >> i & 1) cur += w[i];

    for (int i = 0; i < m; i++) {
      if ((st >> U[i] & 1) && (st >> V[i] & 1)) {
        dsu.merge(U[i], V[i]);
        deg[U[i]]++, deg[V[i]]++;
      }
    }
    int cnt = 0;
    bool flg = false;
    for (int i = 0; i < n; i++) {
      if (st >> i & 1) {
        if (deg[i] & 1) flg = true;
        if (dsu.fa[i] == i) cnt++;
      }
    }
    if (cnt != 1) flg = true;

    if (flg) g[popcnt(st)][st] = fast_pow(cur, p, mod);
    inv[st] = fast_pow(fast_pow(cur, mod - 2, mod), p, mod);
  }

  for (int i = 0; i <= n; i++) fwt(g[i], mask, 1);
  f[0][0] = 1, fwt(f[0], mask, 1);
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < i; j++) {
      for (int k = 0; k < mask; k++) {
        f[i][k] += f[j][k] * g[i - j][k] % mod;
        f[i][k] %= mod;
      }
    }
    fwt(f[i], mask, -1);

    for (int j = 0; j < mask; j++) {
      if (popcnt(j) == i) f[i][j] = inv[j] * f[i][j] % mod;
      else f[i][j] = 0;
    }
    if (i != n) fwt(f[i], mask, 1);
  }

  std::cout << f[n][mask - 1] << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
