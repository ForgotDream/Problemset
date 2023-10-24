/**
 * @file    P2512 糖果传递.cpp
 * @author  ForgotDream
 * @brief   贪心
 * @date    2023-03-19
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
  i64 avg = 0;
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
    avg += a[i];
  }

  avg /= n;

  for (int i = 0; i < n; i++) {
    a[i] -= avg;
  }

  std::vector<i64> sum(n);
  sum[0] = a[0];
  for (int i = 1; i < n; i++) {
    sum[i] = sum[i - 1] + a[i];
  }

  std::sort(sum.begin(), sum.end());

  i64 ans = 0, pivot = sum[(n - 1) / 2];
  for (int i = 0; i < n; i++) {
    ans += std::abs(pivot - sum[i]);
  }
  std::cout << ans << "\n";

  return 0;
}