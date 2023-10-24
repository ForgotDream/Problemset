/**
 * @file    P1435 回文字串.cpp
 * @author  ForgotDream
 * @brief   Interval DP
 * @date    2023-05-31
 */
#include <bits/stdc++.h>

using i64 = long long;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::string s;
  std::cin >> s;

  int n = s.length();
  std::vector f(n, std::vector<int>(n));

  for (int i = 0; i < n; i++) {
    f[i][i] = 0;
  }

  for (int len = 2; len <= n; len++) {
    for (int l = 0; l + len - 1 < n; l++) {
      int r = l + len - 1;
      if (s[l] == s[r]) {
        f[l][r] = f[l + 1][r - 1];
      } else {
        f[l][r] = std::min(f[l][r - 1], f[l + 1][r]) + 1;
      }
    }
  }

  std::cout << f[0][n - 1] << "\n";

  return 0;
}