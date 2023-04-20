/**
 * @file    P7521 取模.cpp
 * @author  ForgotDream
 * @brief   乱搞 or 数学
 * @date    2023-03-25
 */
#include <bits/stdc++.h>

using i64 = long long;
using f80 = long double;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  std::vector<i64> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  std::sort(a.begin(), a.end(), std::greater<i64>());

  i64 ans = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < std::min(i + 20, n); j++) {
      if (i == j) {
        continue;
      }
      if (a[i] + a[j] < ans) {
        continue;
      }
      for (int k = 0; k < std::min(j + 20, n); k++) {
        if (double(std::clock()) / CLOCKS_PER_SEC >= 0.98) {
          std::cout << ans << "\n";
          return 0;
        }
        if (a[k] <= ans) {
          continue;
        }
        if (k == i || k == j) {
          continue;
        }
        ans = std::max(ans, (a[i] + a[j]) % a[k]);
      }
    }
  }

  std::cout << ans << "\n";

  return 0;
}