/**
 * @file    CF246A Buggy Sorting.cpp
 * @author  ForgotDream
 * @brief   shabi
 * @date    2023-09-08
 */
#include <iostream>

using i64 = long long;

int n;
void solve() {
  std::cin >> n;
  if (n <= 2) {
    std::cout << -1 << "\n";
    return;
  }
  for (int i = 2; i <= n; i++) std::cout << i << " ";
  std::cout << 1 << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}