/**
 * @file    P4492 [HAOI2018] 苹果树.cpp
 * @author  ForgotDream
 * @brief   Math
 * @date    2023-08-11
 */
#include <bits/stdc++.h>
using i64 = long long;
constexpr int N = 2050;
int n, p;
i64 f[N][N], c[N][N], fac[N], ans;
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n >> p;
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= i; j++) {
      if (!j) c[i][j] = 1;
      else c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % p;
    }
  }
  fac[0] = 1;
  for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % p;
  f[1][1] = 1;
  for (int i = 2; i <= n; i++) {
    for (int j = 1; j <= i; j++) {
      f[i][j] = j * (j - 1) % p * fac[i - 2] % p;
    }
  }
  for (int i = 2; i <= n; i++) {
    for (int j = 1; j <= n - i + 1; j++) {
      (ans += fac[j] * c[n - i][j - 1] % p * j * (n - j) % p * f[n - j + 1][i] %
              p) %= p;
    }
  }
  std::cout << ans << "\n";
  return 0;
}