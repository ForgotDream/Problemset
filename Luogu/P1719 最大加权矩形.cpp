/**
 * @file    P1719 最大加权矩形.cpp
 * @author  ForgotDream
 * @brief   Prefix sum + DP
 * @date    2023-05-03
 */
#include <bits/stdc++.h>

using i64 = long long;
using i64u = unsigned long long;
using f80 = long double;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  std::vector s(n + 1, std::vector<int>(n + 1));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      int c;
      std::cin >> c;
      s[i][j] = s[i - 1][j] + c;
    }
  }

  int ans = INT_MIN;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= i; j++) {
      int sum = 0;
      for (int k = 1; k <= n; k++) {
        int cur = s[i][k] - s[j - 1][k];
        if (sum < 0) {
          sum = 0;
        }
        sum += cur;
        ans = std::max(ans, sum);
      }
    }
  }

  std::cout << ans << "\n";

  return 0;
}