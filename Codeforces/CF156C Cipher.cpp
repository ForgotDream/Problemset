/**
 * @file    CF156C Cipher.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-09-05
 */
#include <iostream>

using i64 = long long;

constexpr int N = 105, M = 2605, mod = 1e9 + 7;
std::string rst;
int f[N][M];
void init() {
  f[0][0] = 1;
  for (int i = 1; i <= 100; i++) {
    for (int j = i; j <= 26 * i; j++) {
      for (int k = 1; k <= 26 && k <= j; k++) {
        (f[i][j] += f[i - 1][j - k]) %= mod;
      }
    }
  }
}
void solve() {
  std::cin >> rst;
  int sum = 0;
  for (int i = 0; i < rst.length(); i++) sum += rst[i] - 'a' + 1;
  std::cout << f[rst.length()][sum] - 1 << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  init();
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}