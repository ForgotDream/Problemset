/**
 * @file    AT_dp_a Frog 1.cpp
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

  int n;
  std::cin >> n;

  std::vector<int> a(n);
  for (int i = 0; i < n; i++) { std::cin >> a[i]; }

  std::vector<int> f(n, inf);
  f[0] = 0;
  for (int i = 0; i < n; i++) {
    if (i + 1 < n) {
      f[i + 1] = std::min(f[i + 1], f[i] + std::abs(a[i] - a[i + 1]));
    }
    if (i + 2 < n) {
      f[i + 2] = std::min(f[i + 2], f[i] + std::abs(a[i] - a[i + 2]));
    }
  }

  std::cout << f[n - 1] << "\n";

  return 0;
}