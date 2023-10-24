/**
 * @file    P2241 统计方形（数据加强版）.cpp
 * @author  ForgotDream
 * @brief   枚举
 * @date    2023-03-20
 */
#include <bits/stdc++.h>

using i64 = long long;
using f80 = long double;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  if (n > m) {
    std::swap(n, m);
  }

  i64 sum1 = 0, sum2 = (i64(n + 1) * n / 2) * (m * i64(m + 1) / 2);
  for (int i = 1; i <= n; i++) {
    sum1 += (n - i + 1) * (m - i + 1);
  }
  std::cout << sum1 << " ";
  std::cout << sum2 - sum1 << "\n";

  return 0;
}