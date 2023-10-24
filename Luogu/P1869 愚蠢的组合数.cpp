/**
 * @file    P1869 愚蠢的组合数.cpp
 * @author  ForgotDream
 * @brief   Math
 * @date    2023-08-11
 */
#include <bits/stdc++.h>
using i64 = long long;
int t, n, k;
void solve() {
  std::cin >> n >> k;
  if ((n & k) == k) std::cout << 1 << "\n";
  else std::cout << 0 << "\n";
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> t;
  while (t--) solve();
  return 0;
}