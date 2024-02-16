/*
 * @file    CF914G Sum the Fibonacci.cpp
 * @author  ForgotDream
 * @brief   FWT / FMT
 * @date    2024-02-15
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 1e6 + 50, M = 17, mask = 1 << M;
constexpr int mod = 1e9 + 7, inv2 = (mod + 1) / 2;

int n;
i64 a[N], b[N], c[N];

i64 fib[mask], f[M + 1][mask], g[mask], ans[mask];

void fwt_or(i64 *a, int len, int opt) {
  for (int h = 2; h <= len; h <<= 1) {
    for (i64 *j = a; j < a + len; j += h) {
      for (i64 *k = j; k < j + (h >> 1); k++) {
        if (opt == 1) k[h >> 1] = (k[h >> 1] + k[0]) % mod;
        else k[h >> 1] = (k[h >> 1] - k[0] + mod) % mod;
      }
    }
  }
}

void fwt_and(i64 *a, int len, int opt) {
  for (int h = 2; h <= len; h <<= 1) {
    for (i64 *j = a; j < a + len; j += h) {
      for (i64 *k = j; k < j + (h >> 1); k++) {
        if (opt == 1) k[0] = (k[0] + k[h >> 1]) % mod;
        else k[0] = (k[0] - k[h >> 1] + mod) % mod;
      }
    }
  }
}

void fwt_xor(i64 *a, int len, int opt) {
  for (int h = 2; h <= len; h <<= 1) {
    for (i64 *j = a; j < a + len; j += h) {
      for (i64 *k = j; k < j + (h >> 1); k++) {
        i64 p = k[0], q = k[h >> 1];
        k[0] = (p + q) % mod, k[h >> 1] = (p - q + mod) % mod;
        if (opt == -1) (k[0] *= inv2) %= mod, (k[h >> 1] *= inv2) %= mod;
      }
    }
  }
}

inline int popcnt(int u) { return __builtin_popcount(u); }

void solve() {
  std::cin >> n;
  for (int i = 1, u; i <= n; i++) std::cin >> u, a[u]++, b[u]++, c[u]++;

  fib[1] = 1;
  for (int i = 2; i < mask; i++) fib[i] = (fib[i - 1] + fib[i - 2]) % mod;

  for (int i = 0; i < mask; i++) f[popcnt(i)][i] = a[i], a[i] = 0;
  for (int i = 0; i <= M; i++) fwt_or(f[i], mask, 1);
  for (int i = 0; i <= M; i++) {
    std::fill(g, g + mask, 0);
    for (int j = 0; j <= i; j++) {
      for (int k = 0; k < mask; k++) {
        g[k] += f[j][k] * f[i - j][k] % mod;
        g[k] %= mod;
      }
    }
    fwt_or(g, mask, -1);
    for (int j = 0; j < mask; j++) if (popcnt(j) == i) a[j] = g[j];
  }

  fwt_xor(c, mask, 1);
  for (int i = 0; i < mask; i++) c[i] = c[i] * c[i] % mod;
  fwt_xor(c, mask, -1);

  for (int i = 0; i < mask; i++) {
    a[i] = a[i] * fib[i] % mod;
    b[i] = b[i] * fib[i] % mod;
    c[i] = c[i] * fib[i] % mod;
  }

  fwt_and(a, mask, 1), fwt_and(b, mask, 1), fwt_and(c, mask, 1);
  for (int i = 0; i < mask; i++) ans[i] = a[i] * b[i] % mod * c[i] % mod;
  fwt_and(ans, mask, -1);

  i64 res = 0;
  for (int i = 1; i < mask; i <<= 1) res += ans[i];
  std::cout << res % mod << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
