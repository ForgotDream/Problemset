/**
 * @file    AT_dp_d Knapsack 1.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-06-18
 */
#include <bits/stdc++.h>

using i64 = long long;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, W;
  std::cin >> n >> W;

  std::vector<int> v(n), w(n);
  for (int i = 0; i < n; i++) { std::cin >> w[i] >> v[i]; }

  std::vector<i64> f(W + 1);
  for (int i = 0; i < n; i++) {
    for (int j = W; j >= w[i]; j--) {
      f[j] = std::max(f[j], f[j - w[i]] + v[i]);
    }
  }
  std::cout << f[W] << "\n";

  return 0;
}