/**
 * @file    P1313 [NOIP2011 提高组] 计算系数.cpp
 * @author  ForgotDream
 * @brief   Math
 * @date    2023-08-09
 */
#include <bits/stdc++.h>
using i64 = long long;
constexpr int mod = 1e4 + 7;
int a, b, k, n, m, c;
i64 fastPow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> a >> b >> k >> n >> m;
  a = fastPow(a, n, mod), b = fastPow(b, m, mod);
  c = 1;
  for (int i = k - n + 1; i <= k; i++) (c *= i) %= mod;
  for (int i = 1; i <= n; i++) (c *= fastPow(i, mod - 2, mod)) %= mod;
  std::cout << 1ll * a * b * c % mod << "\n";
  return 0;
}