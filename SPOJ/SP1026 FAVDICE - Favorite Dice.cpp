/**
 * @file    SP1026 FAVDICE - Favorite Dice.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-08-16
 */
#include <bits/stdc++.h>
using i64 = long long;
using f80 = long double;
constexpr int N = 1e3 + 50;
int t, n;
f80 f[N][N];
void solve() {
  std::cin >> n;
  std::cout << f[n][1] << "\n";
}
void init() {
  for (int i = 1; i <= 1000; i++) {
    f[i][i] = 1;
    for (int j = i - 1; j >= 1; j--) f[i][j] = f[i][j + 1] + (1. * i / (i - j));
  }
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout << std::fixed << std::setprecision(2);
  init();
  std::cin >> t;
  while (t--) solve();
  return 0;
}