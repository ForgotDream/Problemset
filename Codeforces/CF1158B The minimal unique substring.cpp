/**
 * @file    CF1158B The minimal unique substring.cpp
 * @author  ForgotDream
 * @brief   Ad Hoc
 * @date    2023-08-04
 */
#include <bits/stdc++.h>
using i64 = long long;
int n, k;
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n >> k;
  for (int i = 1; i <= n; i++) std::cout << !!(i % ((n - k) / 2 + 1));
  std::cout << "\n";
  return 0;
}