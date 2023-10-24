/**
 * @file    CF1608D Dominoes.cpp
 * @author  ForgotDream
 * @brief   Math
 * @date    2023-08-07
 */
#include <bits/stdc++.h>
using i64 = long long;
constexpr int N = 2e5 + 50, mod = 998244353;
int n;
std::string s[N];
i64 fastPow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}
i64 fac[N], inv[N];
void init() {
  inv[0] = fac[0] = 1;
  for (int i = 1; i <= 2 * n; i++) {
    fac[i] = (i * fac[i - 1]) % mod;
    inv[i] = fastPow(fac[i], mod - 2, mod);
  }
}
i64 C(int n, int m) {
  if (m < 0 || n < m) return 0;
  return fac[n] * inv[m] % mod * inv[n - m] % mod; 
}
int cnt, cntW, cntB, cntWW, cntBB, cntWB, cntBW;
i64 ans;
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n;
  init();
  for (int i = 1; i <= n; i++) {
    std::cin >> s[i];
    cnt += (s[i][0] != '?') + (s[i][1] != '?');
    cntW += (s[i][0] == 'W') + (s[i][1] == 'W');
    cntB += (s[i][0] == 'B') + (s[i][1] == 'B');
    cntWW += (s[i] == "WW"), cntBB += (s[i] == "BB");
    cntWB += (s[i][0] == 'W' || s[i][1] == 'B');
    cntBW += (s[i][0] == 'B' || s[i][1] == 'W');
  }
  ans = C(2 * n - cnt, n - cntW);
  if (cntWW || cntBB) return std::cout << ans << "\n", 0;
  ans += (!cntWB) + (!cntBW);
  (ans -= fastPow(2, n - cntWB - cntBW, mod)) %= mod;
  (ans += mod) %= mod;
  std::cout << ans << "\n";
  return 0;
}