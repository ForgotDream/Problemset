/**
 * @file    CF1265E Beautiful Mirrors.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-06-29
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int mod = 998244353;

i64 fastPow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  while (exp) {
    if (exp & 1) {
      (res *= base) %= mod;
    }
    (base *= base) %= mod;
    exp >>= 1;
  }
  return res;
}

i64 inv(i64 num) {
  return fastPow(num, mod - 2, mod);
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  std::vector<i64> f(n);
  f[0] = 100ll * inv(a[0]) % mod;
  for (int i = 1; i < n; i++) {
    f[i] = (f[i - 1] + 1) * 100ll % mod * inv(a[i]) % mod;
  }

  std::cout << f[n - 1] << "\n";

  return 0;
}
