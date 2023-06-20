/**
 * @file    AT_dp_b Frog 2.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-06-18
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int inf = 1e9;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, k;
  std::cin >> n >> k;

  std::vector<int> a(n);
  for (int i = 0; i < n; i++) { std::cin >> a[i]; }

  std::vector<int> f(n, inf);
  f[0] = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 1; j <= k && i + j < n; j++) {
      f[i + j] = std::min(f[i + j], f[i] + std::abs(a[i] - a[i + j]));
    }
  }

  std::cout << f[n - 1] << "\n";

  return 0;
}