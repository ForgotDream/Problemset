/*
 * @file    AT_agc002_f [AGC002F] Leftmost Ball.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2024-01-10
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2050, mod = 1e9 + 7;

i64 fac[N * N], ifc[N * N];
inline i64 fastPow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}
inline i64 getInv(i64 u) { return fastPow(u, mod - 2, mod); }
void init(int n) {
  fac[0] = ifc[0] = 1;
  for (int i = 1; i <= n; i++) fac[i] = i * fac[i - 1] % mod;
  ifc[n] = getInv(fac[n]);
  for (int i = n - 1; i; i--) ifc[i] = (i + 1) * ifc[i + 1] % mod;
}
inline i64 C(i64 n, i64 m) { 
  if (n < 0 || m > n) return 0;
  return fac[n] * ifc[m] % mod * ifc[n - m] % mod; 
}

int n, k;

// 先考虑把不更改颜色的方案数算出来，然后再考虑重复的部分？
// 数数题，太恐怖。
// 看了题解发现完全不一样啊！真是太棒了！
// 为什么没想到钦定颜色？有点滞胀了！

i64 f[N][N];

void solve() {
  std::cin >> n >> k;

  if (k == 1) return std::cout << 1 << "\n", void();

  init(n * k);

  f[0][0] = 1;
  for (int i = 0; i < n; i++) {
    for (int j = i; j >= 0; j--) (f[i][j] += f[i][j + 1]) %= mod;
    for (int j = i; j >= 0; j--) {
      f[i + 1][j + 1] += f[i][j] * C(i * k - j + k - 2, k - 2) % mod;
      f[i + 1][j + 1] %= mod;
    }
  }
  for (int i = n; i >= 0; i--) (f[n][i] += f[n][i + 1]) %= mod;

  std::cout << f[n][0] * fac[n] % mod << "\n";
}

signed main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
