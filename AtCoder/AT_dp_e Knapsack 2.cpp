/**
 * @file    AT_dp_e Knapsack 2.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-06-18
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int d = 1e5;
constexpr i64 inf = 1e15;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, W;
  std::cin >> n >> W;

  std::vector<int> v(n), w(n);
  for (int i = 0; i < n; i++) { std::cin >> w[i] >> v[i]; }

  std::vector<i64> f(d + 1, inf);
  f[0] = 0;
  for (int i = 0; i < n; i++) {
    for (int j = d; j >= v[i]; j--) {
      f[j] = std::min(f[j], f[j - v[i]] + w[i]);
    }
  }

  for (int i = d; i >= 0; i--) {
    if (f[i] <= W) {
      std::cout << i << "\n";
      return 0;
    }
  }

  return 0;
}