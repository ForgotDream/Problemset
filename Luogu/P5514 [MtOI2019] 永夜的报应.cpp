/**
 * @file    P5514 [MtOI2019] 永夜的报应.cpp
 * @author  ForgotDream
 * @brief   Math + Bitmask
 * @date    2023-08-15
 */
#include <bits/stdc++.h>
using i64 = long long;
int n, ans;
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n;
  for (int i = 1, u; i <= n; i++) std::cin >> u, ans ^= u;
  std::cout << ans << "\n";
  return 0;
}