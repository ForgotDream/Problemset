/**
 * @file    P5104 红包发红包.cpp
 * @author  ForgotDream
 * @brief   Math
 * @date    2023-08-16
 */
#include <iostream>

using i64 = long long;

constexpr int mod = 1e9 + 7;
int w;
i64 n, k;

// invertion
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

  std::cin >> w >> n >> k;
  
  std::cout << 1ll * w * inv(fastPow(2, k, mod)) % mod << "\n";

  return 0;
}