/**
 * @file    P2111 考场奇遇.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-08-16
 */
#include <bits/stdc++.h>
using i64 = long long;
using f80 = long double;
constexpr int N = 55;
int n, q;
f80 a, f[N][N];
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout << std::fixed << std::setprecision(3);
  std::cin >> n >> a >> q;
  a /= 100;
  if (q == 0) return std::cout << "1.000\n", 0;
  f[0][0] = 1;
  for (int i = 1; i <= n; i++) {
    char c;
    std::cin >> c;
    auto p = (c == '1') ? a : (1 - a);
    for (int j = 0; j <= i; j++) {
      f[i][j] = (1 - p) * f[i - 1][j];
      if (j) f[i][j] += p * f[i - 1][j - 1];
    }
  }
  f80 ans = 0;
  for (int i = q; i <= n; i++) ans += f[n][i];
  std::cout << ans << "\n";
  return 0;
}