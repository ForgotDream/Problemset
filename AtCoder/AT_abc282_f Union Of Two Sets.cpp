/**
 * @file    AT_abc282_f Union Of Two Sets.cpp
 * @author  ForgotDream
 * @brief   Sparse Table
 * @date    2023-05-09
 */
#include <bits/stdc++.h>

using i64 = long long;

signed main() {
  // std::ios::sync_with_stdio(false);
  // std::cin.tie(0);

  int n;
  std::cin >> n;

  std::vector<std::pair<int, int>> a;
  std::vector f(n + 1, std::vector<int>(std::ceil(std::log2(n)) + 1));
  for (int i = 1; i <= n; i++) {
    for (int j = 0; i + (1 << j) - 1 <= n; j++) {
      a.emplace_back(i, i + (1 << j) - 1);
      f[i][j] = a.size() - 1;
    }
  }

  std::cout << a.size() << std::endl;
  for (int i = 0; i < a.size(); i++) {
    std::cout << a[i].first << " " << a[i].second << std::endl;
  }

  int q;
  std::cin >> q;
  
  while (q--) {
    int l, r;
    std::cin >> l >> r;
    int d = std::log2(r - l + 1);
    std::cout << f[l][d] + 1 << " " << f[r - (1 << d) + 1][d] + 1 << std::endl;
  }

  return 0;
}