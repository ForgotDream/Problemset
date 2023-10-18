/**
 * @file    P5323 [BJOI2019] 光线.cpp
 * @author  ForgotDream
 * @brief   Math
 * @date    2023-10-18
 */
#include <iostream>

using i64 = long long;

constexpr int N = 5e5 + 50, mod = 1e9 + 7;
i64 fastPow(i64 base, i64 exp, i64 mod) {
  base %= mod;
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}
i64 inv(i64 u) { return fastPow(u, mod - 2, mod); }
int n;
i64 a[N], b[N];
void solve() {
  std::cin >> n;
  i64 tmp = inv(100);
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i] >> b[i];
    a[i] = tmp * a[i] % mod, b[i] = tmp * b[i] % mod;
  }
  for (int i = n - 1; i >= 1; i--) {
    i64 tmp = inv(1 - b[i] * b[i + 1] % mod + mod);
    i64 c = a[i] * a[i + 1] % mod * tmp % mod;
    i64 d = (b[i] + a[i] * a[i] % mod * b[i + 1] % mod * tmp % mod) % mod;
    a[i] = c, b[i] = d;
  }
  std::cout << a[1] << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
