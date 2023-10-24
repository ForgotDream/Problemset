/**
 * @file    CF603B Moodular Arithmetic.cpp
 * @author  ForgotDream
 * @brief   Math
 * @date    2023-08-29
 */
#include <iostream>

using i64 = long long;

constexpr int mod = 1e9 + 7;
int p, k;
i64 fastPow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}
void solve() {
  std::cin >> p >> k;
  if (!k) return void(std::cout << fastPow(p, p - 1, mod) << "\n");
  if (k == 1) return void(std::cout << fastPow(p, p, mod) << "\n");
  i64 m = 1, cpy = k;
  while (cpy != 1) m++, (cpy *= k) %= p;
  std::cout << fastPow(p, (p - 1) / m, mod) << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}