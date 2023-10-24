/**
 * @file    P1088 火星人.cpp
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

  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  while (m--) {
    std::next_permutation(a.begin(), a.end());
  }

  for (int i = 0; i < n; i++) {
    std::cout << a[i] << " \n"[i == n - 1];
  }

  return 0;
}