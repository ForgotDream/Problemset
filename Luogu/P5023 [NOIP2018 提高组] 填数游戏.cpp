/*
 * @file    P5023 [NOIP2018 提高组] 填数游戏.cpp
 * @author  ForgotDream
 * @brief   Math
 * @date    2024-02-01
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int mod = 1e9 + 7;

int n, m;

inline i64 fast_pow(i64 base, i64 exp, i64 mod = ::mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}

void solve() {
  std::cin >> n >> m;
  if (n > m) std::swap(n, m);

  i64 res;
  if (n == 1) {
    res = fast_pow(2, m);
  } else if (n == 2) {
    res = 4 * fast_pow(3, m - 1) % mod;
  } else if (n == 3) {
    res = 112 * fast_pow(3, m - 3) % mod;
  } else {
    if (m == n) {
      res = 83 * fast_pow(8, n) % mod + 5 * fast_pow(2, n + 7) % mod;
      res = res * 190104168 % mod;
    } else {
      res = 83 * fast_pow(8, n) % mod + fast_pow(2, n + 8);
      res = res * fast_pow(3, m - n - 1) % mod;
      res = res * 570312504 % mod;
    }
  }
  std::cout << res << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
