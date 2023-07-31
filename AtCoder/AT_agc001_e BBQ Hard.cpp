/**
 * @file    AT_agc001_e BBQ Hard.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-07-26
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int mod = 1e9 + 7, N = 2e5 + 50, M = 2050, D = 2001;
int n, a[N], b[N];
i64 fac[4 * M], f[2 * M][2 * M];

i64 fastPow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}
i64 inv(i64 num) { return fastPow(num, mod - 2, mod); }
i64 C(int n, int m) { return fac[n] * inv(fac[m]) % mod * inv(fac[n - m]) % mod; }

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  fac[0] = 1;
  for (int i = 1; i <= 8000; i++) fac[i] = i * fac[i - 1] % mod;

  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i] >> b[i], f[D - a[i]][D - b[i]]++;

  for (int i = 1; i <= 2 * D; i++) {
    for (int j = 1; j <= 2 * D; j++) {
      (f[i][j] += f[i - 1][j] + f[i][j - 1]) %= mod;
    }
  }
  i64 ans = 0;
  for (int i = 1; i <= n; i++) {
    (ans += f[D + a[i]][D + b[i]]) %= mod;
    (ans -= C(2 * (a[i] + b[i]), 2 * a[i])) %= mod;
    (ans += mod) %= mod;
  }
  (ans *= inv(2)) %= mod;

  std::cout << ans << "\n";

  return 0;
}