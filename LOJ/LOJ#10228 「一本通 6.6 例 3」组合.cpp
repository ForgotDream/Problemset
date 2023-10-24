/**
 * @file    LOJ#10228 「一本通 6.6 例 3」组合.cpp
 * @author  ForgotDream
 * @brief   Math
 * @date    2023-08-09
 */
#include <bits/stdc++.h>
using i64 = long long;
int t;
i64 n, m, p;
i64 fastPow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}
i64 inv(i64 num) { return fastPow(num, p - 2, p); }
i64 C(int n, int m) {
  if (m > n) return 0;
  i64 res = 1;
  for (int i = n - m + 1; i <= n; i++) (res *= i) %= p;
  for (int i = 1; i <= m; i++) (res *= inv(i)) %= p;
  return res;
}
i64 lucas(i64 n, i64 m) {
  if (!m) return 1ll;
  return C(n % p, m % p) * lucas(n / p, m / p) % p;
}
void solve() {
  std::cin >> n >> m >> p;
  std::cout << lucas(n, m) << "\n";
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> t;
  while (t--) solve();
  return 0;
}