/**
 * @file    P4781 拉格朗日插值.cpp
 * @author  ForgotDream
 * @brief   Lagrange Interpolation
 * @date    2023-05-05
 */
#include <bits/stdc++.h>

using i64 = long long;
using i64u = unsigned long long;
using f80 = long double;

constexpr int MOD = 998244353;

i64 fastPow(i64 base, i64 pow, i64 mod) {
  i64 res = 1;

  while (pow) {
    if (pow & 1) {
      (res *= base) %= MOD;
    }
    (base *= base) %= MOD;
    pow >>= 1;
  }

  return res;
}

i64 lagrange(int n, const std::vector<int> &x, const std::vector<int> &y, int k) {
  i64 res = 0;

  for (int i = 0; i <= n; i++) {
    i64 prod1 = 1, prod2 = 1;
    for (int j = 0; j <= n; j++) {
      if (i != j) {
        (prod1 *= (k - x[j])) %= MOD;
        (prod2 *= (x[i] - x[j])) %= MOD;
      }
    }
    (res += y[i] * prod1 % MOD * fastPow(prod2, MOD - 2, MOD)) %= MOD;
  }

  return (res + MOD) % MOD;
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, k;
  std::cin >> n >> k;

  std::vector<int> x(n), y(n);
  for (int i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
  }

  std::cout << lagrange(n - 1, x, y, k) << "\n";

  return 0;
}