/**
 * @file    P4859 已经没有什么好害怕的了.cpp
 * @author  ForgotDream
 * @brief   Math
 * @date    2023-08-14
 */
#include <bits/stdc++.h>
using i64 = long long;
constexpr int N = 2050, mod = 1e9 + 9;
int n, k;
i64 a[N], b[N], c[N];
i64 dp[N][N], g[N];
i64 fac[N], inv[N];
i64 fastPow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}
void init() {
  fac[0] = inv[0] = 1;
  for (int i = 1; i <= n; i++) {
    fac[i] = i * fac[i - 1] % mod;
    inv[i] = fastPow(fac[i], mod - 2, mod);
  }
}
i64 C(i64 n, i64 m) { return fac[n] * inv[m] % mod * inv[n - m] % mod; }
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n >> k;
  init();
  if ((n - k) % 2 != 0) return std::cout << 0 << "\n", 0;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  for (int i = 1; i <= n; i++) std::cin >> b[i];
  std::sort(a + 1, a + n + 1), std::sort(b + 1, b + n + 1);
  int p = 1;
  for (int i = 1; i <= n; i++) {
    while (p <= n && b[p] < a[i]) p++;
    c[i] = p - 1;
  }
  dp[0][0] = 1;
  for (int i = 1; i <= n; i++) {
    dp[i][0] = dp[i - 1][0];
    for (int j = 1; j <= i; j++) {
      dp[i][j] = dp[i - 1][j];
      if (c[i] - j + 1 >= 0) {
        (dp[i][j] += dp[i - 1][j - 1] * (c[i] - j + 1)) %= mod;
      }
    }
  }
  for (int i = 0; i <= n; i++) g[i] = fac[n - i] * dp[n][i] % mod;
  i64 f = 0;
  k = (n + k) / 2;
  for (int i = k; i <= n; i++) {
    i64 d = (i - k) % 2 ? -1 : 1;
    (f += d * C(i, k) % mod * g[i] % mod) %= mod;
  }
  std::cout << (f + mod) % mod << "\n";
  return 0;
}