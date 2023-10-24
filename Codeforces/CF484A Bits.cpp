/**
 * @file    CF484A Bits.cpp
 * @author  ForgotDream
 * @brief   Bitmasks + Greedy
 * @date    2023-08-25
 */
#include <iostream>

using i64 = long long;

i64 l, r;
void solve() {
  std::cin >> l >> r;
  for (i64 i = 1; (l | i) <= r; i <<= 1) l |= i;
  std::cout << l << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}