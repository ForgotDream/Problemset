/**
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2023-06-16
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int mod = 1e9 + 7;

i64 fastPow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  while (exp) {
    if (exp & 1) { (res *= base) %= mod; }
    (base *= base) %= mod;
    exp >>= 1;
  }
  return res;
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int s, t, k;
  std::cin >> s >> t >> k;

  if (s > t) { std::swap(s, t); }
  int d = t - s;

  if (k < d) {
    std::cout << 0 << "\n";
    return 0;
  } else if (k == d) {
    std::cout << 1 << "\n";
    return 0;
  }

  std::vector<i64> fac(std::max({s, t, k}) + 1);
  fac[0] = 1;
  for (int i = 1; i < fac.size(); i++) { (fac[i] = fac[i - 1] * i) %= mod; }
  auto C = [&](int n, int m) -> i64 { 
    if (n < 0 || m < 0 || m > n) { return 0ll; }
    return fac[n] 
         * fastPow(fac[m], mod - 2, mod) % mod
         * fastPow(fac[n - m], mod - 2, mod) % mod;
  };

  i64 ans = 0;
  for (int i = 0; i <= k; i++) {
    if ((i + t - s) & 1) { continue; }
    int x = (i - t + s) >> 1, y = (i + t - s) >> 1;
    if (x < 0) { continue; }
    (ans += C(x + y, x)) %= mod;
    if (x > s) { (ans -= C(x + y, x - s - 1)) %= mod; }
  }

  (ans += mod) %= mod;
  std::cout << ans << "\n";

  return 0;
}