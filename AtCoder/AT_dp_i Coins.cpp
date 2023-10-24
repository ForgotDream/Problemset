/**
 * @file    AT_dp_i Coins.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-06-18
 */
#include <bits/stdc++.h>

using i64 = long long;
using f80 = long double;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout << std::fixed << std::setprecision(12);

  int n;
  std::cin >> n;

  std::vector<f80> a(n);
  for (int i = 0; i < n; i++) { std::cin >> a[i]; }

  std::vector f(n, std::vector<f80>(n + 1));
  f[0][0] = 1 - a[0], f[0][1] = a[0];
  for (int i = 1; i < n; i++) {
    for (int j = 0; j <= n; j++) {
      f[i][j] += f[i - 1][j] * (1 - a[i]);
      f[i][j] += (j ? f[i - 1][j - 1] : 0) * a[i];
    }
  }

  f80 ans = 0;
  for (int i = 0; i <= n; i++) {
    if (i > n - i) { ans += f[n - 1][i]; }
  }
  std::cout << ans << "\n";

  return 0;
}