/**
 * @file    P3736 字符合并.cpp
 * @author  ForgotDream
 * @brief   Interval DP
 * @date    2023-06-07
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr i64 inf = 1e12;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, k;
  std::cin >> n >> k;
  int m = 1 << k;

  std::vector<int> a(n);
  for (int i = 0; i < n; i++) { std::cin >> a[i]; }

  std::vector<int> c(m), w(m);
  for (int i = 0; i < m; i++) { std::cin >> c[i] >> w[i]; }

  std::vector f(n, std::vector(n, std::vector<i64>(m, -inf)));
  for (int i = 0; i < n; i++) { f[i][i][a[i]] = 0; }

  for (int len = 2; len <= n; len++) {
    for (int l = 0; l + len - 1 < n; l++) {
      int r = l + len - 1, curLen = (len - 1) % (k - 1);
      if (!curLen) { curLen = k - 1; }

      for (int p = r; p > l; p -= (k - 1)) {
        for (int st = 0; st < (1 << curLen); st++) {
          f[l][r][st << 1] = std::max(
            f[l][r][st << 1], 
            f[l][p - 1][st] + f[p][r][0]
          );
          f[l][r][st << 1 | 1] = std::max(
            f[l][r][st << 1 | 1], 
            f[l][p - 1][st] + f[p][r][1]
          );
        }
      }

      if (curLen == k - 1) {
        i64 max1 = -inf, max0 = -inf;
        for (int st = 0; st < m; st++) {
          if (c[st]) {
            max1 = std::max(max1, f[l][r][st] + w[st]);
          } else {
            max0 = std::max(max0, f[l][r][st] + w[st]);
          }
        }
        f[l][r][0] = max0, f[l][r][1] = max1;
      }
    }
  }

  i64 ans = -inf;
  for (int i = 0; i < m; i++) { ans = std::max(ans, f[0][n - 1][i]); }
  std::cout << ans << "\n";

  return 0;
}