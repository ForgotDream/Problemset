/**
 * @file    CF1753C Wish I Knew How to Sort.cpp
 * @author  ForgotDream
 * @brief   DP + Math
 * @date    2023-08-06
 */
#include <bits/stdc++.h>
using i64 = long long;
constexpr int N = 2e5 + 50, mod = 998244353;
int t, n, a[N], cnt, w;
i64 f[N];
i64 fastPow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}
i64 inv(i64 num) { return fastPow(num, mod - 2, mod); }
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  cnt = std::count(a + 1, a + n + 1, 0);
  w = std::count(a + 1, a + cnt + 1, 0);
  f[w] = 0;
  for (int i = w + 1; i <= cnt; i++) {
    f[i] = f[i - 1] + (1ll * n * (n - 1) / 2) % mod *
                          inv(1ll * (cnt - i + 1) * (cnt - i + 1) % mod) % mod;
    f[i] %= mod;
  }
  std::cout << f[cnt] << "\n";
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> t;
  while (t--) solve();
  return 0;
}