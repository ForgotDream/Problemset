/**
 * @file    AT_dp_c Vacation.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-06-18
 */
#include <bits/stdc++.h>

using i64 = long long;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  std::vector a(n, std::vector<int>(3));
  for (int i = 0; i < n; i++) { std::cin >> a[i][0] >> a[i][1] >> a[i][2]; }

  std::vector f(n, std::vector<int>(3));
  for (int i = 0; i < 3; i++) { f[0][i] = a[0][i]; }
  for (int i = 1; i < n; i++) {
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < 3; k++) {
        if (j == k) { continue; }
        f[i][j] = std::max(f[i][j], f[i - 1][k] + a[i][j]);
      }
    }
  }
  std::cout << *std::max_element(f[n - 1].begin(), f[n - 1].end()) << "\n";

  return 0;
}