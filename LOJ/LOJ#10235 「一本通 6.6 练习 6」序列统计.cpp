/**
 * @file    LOJ#10235 「一本通 6.6 练习 6」序列统计.cpp
 * @author  ForgotDream
 * @brief   Math
 * @date    2023-08-10
 */
#include <bits/stdc++.h>
using i64 = long long;
constexpr int mod = 1e6 + 3;
int t, n, l, r;
i64 fastPow(i64  base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}
int C(int n, int m) {
  i64 a = 1, b = 1;
  for (int i = n - m + 1; i <= n; i++) (a *= i) %= mod;
  for (int i = 1; i <= m; i++) (b *= i) %= mod;
  return 1ll * a * fastPow(b, mod - 2, mod) % mod;
}
int lucas(int n, int m) {
  if (!m) return 1;
  return 1ll * C(n % mod, m % mod) * lucas(n / mod, m / mod) % mod;
}
void solve() {
  std::cin >> n >> l >> r;
  int m = r - l + 1;
  std::cout << (lucas(m + n, m) - 1 + mod) % mod << "\n";
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> t;
  while (t--) solve();
  return 0;
}