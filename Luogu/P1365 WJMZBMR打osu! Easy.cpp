/**
 * @file    P1365 WJMZBMR打osu! / Easy.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-08-16
 */
#include <bits/stdc++.h>

using i64 = long long;
using f80 = long double;

constexpr int N = 3e5 + 50;
constexpr int C[][5] = {{1}, {1, 1}, {1, 2}, {1, 3, 3}, {1, 4, 6, 4, 1}};
int n, k;
f80 a[N], f[N], tmp[4];

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout << std::fixed << std::setprecision(4);

  std::cin >> n;
  k = 2;
  for (int i = 1; i <= n; i++) {
    char c;
    std::cin >> c;
    if (c == 'o') a[i] = 1;
    else if (c == 'x') a[i] = 0;
    else a[i] = 0.5;
  }
  
  for (int i = 1; i <= n; i++) {
    f[i] = f[i - 1] +
           a[i] * (C[k][1] * tmp[1] + C[k][2] * tmp[2] + C[k][3] * tmp[3] + 1);
    tmp[3] = a[i] * (tmp[3] + 3 * tmp[2] + 3 * tmp[1] + 1);
    tmp[2] = a[i] * (tmp[2] + 2 * tmp[1] + 1);
    tmp[1] = a[i] * (tmp[1] + 1);
  }
  std::cout << f[n] << "\n";

  return 0;
}