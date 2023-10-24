/**
 * @file    CF1618A Polycarp and Sums of Subsequences.cpp
 * @author  ForgotDream
 * @brief   shabi
 * @date    2023-09-08
 */
#include <algorithm>
#include <iostream>
#include <vector>

using i64 = long long;

i64 a[8];
void solve() {
  for (int i = 0; i < 7; i++) std::cin >> a[i];
  std::cout << a[0] << " " << a[1] << " ";
  if (a[2] == a[0] + a[1]) std::cout << a[3] << "\n";
  else std::cout << a[2] << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}