/**
 * @file    CF762D Maximum path.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-10-31
 */
#include <algorithm>
#include <iostream>

using i64 = long long;

constexpr int N = 1e5 + 50, M = 5;
int n;
i64 a[M][N], f[M][N];
// 很玄妙的题
void solve() {
  std::cin >> n;
  for (int i = 1; i <= 3; i++) {
    for (int j = 1; j <= n; j++) std::cin >> a[i][j];
  }
  f[1][1] = a[1][1], f[2][1] = f[1][1] + a[2][1], f[3][1] = f[2][1] + a[3][1];
  i64 max1 = a[1][1] + a[2][1] + a[3][1], max3 = -1e18;
  for (int i = 2; i <= n; i++) {
    f[1][i] = std::max({f[1][i - 1], f[2][i - 1] + a[2][i], f[3][i - 1] + a[3][i] + a[2][i]}) + a[1][i];
    f[2][i] = std::max({f[1][i - 1] + a[1][i], f[2][i - 1], f[3][i - 1] + a[3][i]}) + a[2][i];
    f[3][i] = std::max({f[1][i - 1] + a[1][i] + a[2][i], f[2][i - 1] + a[2][i], f[3][i - 1]}) + a[3][i];
    // 三种常规转移
    max1 = std::max(max1, f[1][i - 1]) + a[1][i] + a[2][i] + a[3][i];
    max3 = std::max(max3, f[3][i - 1]) + a[1][i] + a[2][i] + a[3][i];
    f[1][i] = std::max(max3, f[1][i]);
    f[3][i] = std::max(max1, f[3][i]);
  }
  std::cout << f[3][n] << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
