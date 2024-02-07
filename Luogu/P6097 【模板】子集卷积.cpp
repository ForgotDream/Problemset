/*
 * @file    P6097 【模板】子集卷积.cpp
 * @author  ForgotDream
 * @brief   FWT / FMT
 * @date    2024-02-07
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 20, mod = 1e9 + 9;

int n;
i64 a[N + 1][1 << N], b[N + 1][1 << N], g[N + 1][1 << N];

void fwt(i64 *f, int len, int opt) {
  for (int h = 2; h <= len; h <<= 1) {
    for (i64 *j = f; j < f + len; j += h) {
      for (i64 *k = j; k < j + (h >> 1); k++) {
        if (opt == 1) k[h >> 1] = (k[h >> 1] + k[0]) % mod;
        else k[h >> 1] = (k[h >> 1] - k[0] + mod) % mod;
      }
    }
  }
}

inline int popcnt(int u) { return __builtin_popcount(u); }

void solve() {
  std::cin >> n;
  int m = 1 << n;
  for (int i = 0; i < m; i++) std::cin >> a[popcnt(i)][i];
  for (int i = 0; i < m; i++) std::cin >> b[popcnt(i)][i];

  for (int i = 0; i <= n; i++) fwt(a[i], m, 1), fwt(b[i], m, 1);
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= i; j++) {
      for (int k = 0; k < m; k++) {
        g[i][k] = (g[i][k] + a[j][k] * b[i - j][k] % mod) % mod;
      }
    }
  }
  for (int i = 0; i <= n; i++) fwt(g[i], m, -1);
  
  for (int i = 0; i < m; i++) std::cout << g[popcnt(i)][i] << " \n"[i == m - 1];
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
