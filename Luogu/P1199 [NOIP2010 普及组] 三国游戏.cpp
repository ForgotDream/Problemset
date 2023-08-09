/**
 * @file    P1199 [NOIP2010 普及组] 三国游戏.cpp
 * @author  ForgotDream
 * @brief   Greedy
 * @date    2023-08-07
 */
#include <bits/stdc++.h>
using i64 = long long;
constexpr int N = 550;
int n, a[N][N], ans;
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n;
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      std::cin >> a[i][j], a[j][i] = a[i][j];
    }
  }
  for (int i = 1; i <= n; i++) {
    std::sort(a[i] + 1, a[i] + n + 1);
    ans = std::max(ans, a[i][n - 1]);
  }
  std::cout << "1\n" << ans << "\n";
  return 0;
}