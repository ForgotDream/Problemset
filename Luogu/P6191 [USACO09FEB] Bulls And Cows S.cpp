/**
 * @file    P6191 [USACO09FEB] Bulls And Cows S.cpp
 * @author  ForgotDream
 * @brief   Math
 * @date    2023-08-09
 */
#include <bits/stdc++.h>
using i64 = long long;
constexpr int mod = 5000011, N = 1e5 + 50;
int n, k;
i64 fac[N], inv[N], ans;
i64 fastPow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}
i64 C(i64 n, i64 m) { return fac[n] * inv[m] % mod * inv[n - m] % mod; }
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n >> k, n++;
  fac[0] = inv[0] = 1;
  for (int i = 1; i <= n; i++) {
    fac[i] = i * fac[i - 1] % mod;
    inv[i] = fastPow(fac[i], mod - 2, mod);
  }
  for (int i = 1; 2 * i <= n; i++) {
    (ans += C(n - i, i)) %= mod;
    n -= k - 1;
  }
  std::cout << ans + 1 << "\n";
  return 0;
}