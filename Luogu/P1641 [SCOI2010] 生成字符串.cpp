/**
 * @file    P1641 [SCOI2010] 生成字符串.cpp
 * @author  ForgotDream
 * @brief   Math
 * @date    2023-08-11
 */
#include <bits/stdc++.h>
using i64 = long long;
constexpr int N = 2e6 + 50, mod = 20100403;
int n, m;
i64 fac[N], inv[N];
i64 fastPow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}
void init(int n) {
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
  std::cin >> n >> m;
  init(n + m);
  std::cout << (C(n + m, n) - C(n + m, n + 1) + mod) % mod << "\n";
  return 0;
}