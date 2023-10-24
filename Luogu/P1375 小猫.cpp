/**
 * @file    P1375 小猫.cpp
 * @author  ForgotDream
 * @brief   Math
 * @date    2023-08-11
 */
#include <bits/stdc++.h>
using i64 = long long;
constexpr int mod = 1e9 + 7;
int n;
i64 fastPow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}
i64 inv(i64 num) { return fastPow(num, mod - 2, mod); }
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n;
  i64 ans = 1;
  for (int i = n + 2; i <= 2 * n; i++) (ans *= i) %= mod;
  for (int i = 1; i <= n; i++) (ans *= inv(i)) %= mod;
  std::cout << ans << "\n";
  return 0;
}