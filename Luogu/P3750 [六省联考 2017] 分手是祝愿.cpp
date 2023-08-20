/**
 * @file    P3750 [六省联考 2017] 分手是祝愿.cpp
 * @author  ForgotDream
 * @brief   Math + DP
 * @date    2023-08-17
 */
#include <iostream>

using i64 = long long;

constexpr int N = 1e5 + 50, mod = 100003;
int n, k, a[N];
i64 f[N];

// invertion
i64 fastPow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}
i64 inv(i64 num) { return fastPow(num, mod - 2, mod); }

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n >> k;
  for (int i = 1; i <= n; i++) std::cin >> a[i];

  int cnt = 0;
  for (int i = n; i >= 1; i--) {
    if (!a[i]) continue;
    cnt++;
    for (int j = 1; j * j <= i; j++) {
      if (i % j == 0) {
        a[j] ^= 1;
        if (j * j != i) a[i / j] ^= 1;
      }
    }
  }
  for (int i = n; i >= 1; i--) {
    f[i] = inv(i) * (n + (n - i) * f[i + 1] % mod) % mod;
  }

  i64 ans = 0;
  if (cnt <= k) {
    ans = cnt;
  } else {
    for (int i = cnt; i > k; i--) (ans += f[i]) %= mod;
    (ans += k) %= mod;
  }
  for (int i = 1; i <= n; i++) (ans *= i) %= mod;
  std::cout << ans << "\n";

  return 0;
}