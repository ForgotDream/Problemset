/**
 * @file    P4550 收集邮票.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-08-16
 */
#include <iostream>
#include <iomanip>

using i64 = long long;
using f80 = long double;

constexpr int N = 1e4 + 50;
int n;
f80 f[N], g[N];

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout << std::fixed << std::setprecision(2);

  std::cin >> n;

  for (int i = n - 1; i >= 0; i--) {
    f[i] = f[i + 1] + 1. * n / (n - i);
    g[i] = 1. * i / (n - i) * f[i] + f[i + 1] + g[i + 1] + 1. * n / (n - i);
  }
  std::cout << g[0] << "\n";

  return 0;
}