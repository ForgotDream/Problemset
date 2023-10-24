/**
 * @file    P6076 [JSOI2015] 染色问题.cpp
 * @author  ForgotDream
 * @brief   容斥
 * @date    2023-08-12
 */
#include <bits/stdc++.h>
using i64 = long long;
constexpr int mod = 1e9 + 7, N = 450;
int n, m, c;
i64 C[N][N], f[N];
i64 fastPow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}
void init() {
  for (int i = 0; i <= 400; i++) {
    for (int j = 0; j <= i; j++) {
      if (!j) C[i][j] = 1;
      else C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
    }
  }
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  init();
  std::cin >> n >> m >> c;
  for (int i = 1; i <= c; i++) {
    i64 cur = 0, k = 1;
    for (int j = m; j >= 1; j--, k = k * (i + 1) % mod) {
      if (j & 1) (cur += fastPow(k - 1, n, mod) * C[m][j] % mod) %= mod;
      else (cur -= fastPow(k - 1, n, mod) * C[m][j] % mod - mod) %= mod;
    }
    f[i] = (fastPow(fastPow(i + 1, m, mod) - 1, n, mod) - cur + mod) % mod;
  }
  i64 ans = f[c];
  for (int i = 1; i <= c; i++) {
    if (i & 1) (ans -= f[c - i] * C[c][i] - mod) %= mod;
    else (ans += f[c - i] * C[c][i]) %= mod;
  }
  std::cout << (ans + mod) % mod << "\n";
  return 0;
}