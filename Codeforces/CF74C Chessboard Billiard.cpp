/**
 * @file    CF74C Chessboard Billiard.cpp
 * @author  ForgotDream
 * @brief   Ad Hoc
 * @date    2023-09-05
 */
#include <iostream>
#include <numeric>

using i64 = long long;

int n, m;
void solve() {
  std::cin >> n >> m;
  std::cout << std::gcd(n - 1, m - 1) + 1 << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}