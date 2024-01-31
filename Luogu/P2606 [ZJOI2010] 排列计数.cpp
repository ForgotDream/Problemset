/*
 * @file    P2606 [ZJOI2010] 排列计数.cpp
 * @author  ForgotDream
 * @brief   Math
 * @date    2024-01-31
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 1e6 + 50;

int n, mod;

i64 fac[N], ifc[N];

inline i64 fast_pow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}

void init(int _n) {
  fac[0] = ifc[0] = 1;
  for (int i = 1; i <= _n; i++) fac[i] = i * fac[i - 1] % mod;
  ifc[_n] = fast_pow(fac[_n], mod - 2, mod);
  for (int i = _n - 1; i; i--) ifc[i] = (i + 1) * ifc[i + 1] % mod;
}

inline i64 C(i64 n, i64 m) {
  if (m > n) return 0;
  return fac[n] * ifc[m] % mod * ifc[n - m] % mod;
}

i64 lucas(i64 n, i64 m) {
  if (!m) return 1;
  return C(n % mod, m % mod) * lucas(n / mod, m / mod);
}

i64 f[N], siz[N];

inline int lc(int u) { return u << 1; }
inline int rc(int u) { return u << 1 | 1; }

void dfs1(int u) {
  if (u > n) return;
  dfs1(lc(u)), dfs1(rc(u));
  siz[u] = 1 + siz[lc(u)] + siz[rc(u)];
}

i64 calc(int u) {
  if (u > n) return 1;
  return lucas(siz[u] - 1, siz[lc(u)]) * calc(lc(u)) % mod * calc(rc(u)) % mod;
}

void solve() {
  std::cin >> n >> mod;
  init(std::min(n, mod - 1));

  dfs1(1);
  std::cout << calc(1) << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
