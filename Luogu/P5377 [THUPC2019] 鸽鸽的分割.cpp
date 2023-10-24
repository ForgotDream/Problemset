/**
 * @file    P5377 [THUPC2019] 鸽鸽的分割.cpp
 * @author  ForgotDream
 * @brief   Math
 * @date    2023-08-07
 */
#include <bits/stdc++.h>
using i64 = long long;
int n;
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  while (std::cin >> n) {
    std::cout << 1 + (n * n * n * n - 6 * n * n * n + 23 * n * n - 18 * n) / 24
              << "\n";
  }
  return 0;
}