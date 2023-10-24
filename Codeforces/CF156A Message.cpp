/**
 * @file    CF156A Message.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-09-05
 */
#include <cstring>
#include <iostream>

using i64 = long long;

constexpr int N = 2050;
char a[N], b[N];
int f[N][N];
void solve() {
  std::cin >> (a + 1) >> (b + 1);
  int n = std::strlen(a + 1), m = std::strlen(b + 1);
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      f[i][j] = f[i - 1][j - 1] + (a[i] == b[j]);
      ans = std::max(ans, f[i][j]);
    }
  }
  std::cout << m - ans << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}