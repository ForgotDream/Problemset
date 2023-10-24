/**
 * @file    P1350 车的放置.cpp
 * @author  ForgotDream
 * @brief   Math
 * @date    2023-08-09
 */
#include <bits/stdc++.h>
using i64 = long long;
constexpr int N = 2050, mod = 1e5 + 3;
i64 a, b, c, d, k, ans;
i64 fac[N], inv[N];
i64 fastPow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}
void init() {
  fac[0] = inv[0] = 1;
  for (int i = 1; i <= 2000; i++) {
    (fac[i] = 1ll * fac[i - 1] * i) %= mod;
    inv[i] = fastPow(fac[i], mod - 2, mod);
  }
}
i64 C(i64 n, i64 m) {
  if (m > n) return 0;
  return fac[n] * inv[m] % mod * inv[n - m] % mod;
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  init();
  std::cin >> a >> b >> c >> d >> k;
  for (int i = 0; i <= k; i++) {
    (ans += 1ll * C(a, i) * C(b, i) % mod * fac[i] % mod * C(c + a - i, k - i) %
            mod * C(d, k - i) % mod * fac[k - i] % mod) %= mod;
  }
  std::cout << ans << "\n";
  return 0;
}