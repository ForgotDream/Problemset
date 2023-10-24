/**
 * @file    P1287 盒子与球.cpp
 * @author  ForgotDream
 * @brief   Math
 * @date    2023-08-15
 */
#include <bits/stdc++.h>
using i64 = long long;
constexpr int N = 15;
int n, m;
i64 fac[N];
i64 fastPow(i64 base, i64 exp, i64 mod = LLONG_MAX) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}
void init() {
  fac[0] = 1;
  for (int i = 1; i <= m; i++) fac[i] = i * fac[i - 1];
}
i64 C(i64 n, i64 m) { return fac[n] / (fac[m] * fac[n - m]); }
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n >> m;
  init();
  i64 ans = 0;
  for (int i = 0; i <= m; i++) {
    i64 d = (m - i) % 2 ? -1 : 1;
    ans += d * C(m, i) * fastPow(i, n);
  }
  std::cout << ans << "\n";
  return 0;
}