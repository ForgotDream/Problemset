/**
 * @file    P1220 关路灯.cpp
 * @author  ForgotDream
 * @brief   Interval DP
 * @date    2023-06-02
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int inf = 1e9;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, c;
  std::cin >> n >> c;
  c--;

  std::vector<int> a(n), b(n), sum(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i] >> b[i];
  }
  std::partial_sum(b.begin(), b.end(), sum.begin());

  std::vector f(n, std::vector(n, std::vector<int>(2, inf)));
  f[c][c][0] = f[c][c][1] = 0;
  for (int len = 2; len <= n; len++) {
    for (int l = 0; l + len - 1 < n; l++) {
      int r = l + len - 1;
      f[l][r][0] = std::min(
        f[l + 1][r][0] + (a[l + 1] - a[l]) * (sum[n - 1] + sum[l] - sum[r]),
        f[l + 1][r][1] + (a[r] - a[l]) * (sum[n - 1] + sum[l] - sum[r])
      );
      f[l][r][1] = std::min(
        f[l][r - 1][1] + (a[r] - a[r - 1]) * (sum[n - 1] + (l ? sum[l - 1] : 0) - sum[r - 1]),
        f[l][r - 1][0] + (a[r] - a[l]) * (sum[n - 1] + (l ? sum[l - 1] : 0) - sum[r - 1])
      );
    }
  }

  std::cout << std::min(f[0][n - 1][0], f[0][n - 1][1]) << "\n";

  return 0;
}
