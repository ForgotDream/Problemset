/**
 * @file    B3611 传递闭包.cpp
 * @author  ForgotDream
 * @brief   Transitive Closure
 * @date    2023-05-09
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 100;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int n;
  std::cin >> n;

  std::vector<std::bitset<N>> a(n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      bool c;
      std::cin >> c;
      a[i][j] = c;
    }
  }

  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      if (a[i][k]) {
        a[i] = a[i] | a[k];
      }
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      std::cout << a[i][j] << " \n"[j == n - 1];
    }
  }

  return 0;
}