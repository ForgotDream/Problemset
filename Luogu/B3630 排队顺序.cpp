/**
 * @file    B3630 排队顺序.cpp
 * @author  ForgotDream
 * @brief   Simulation
 * @date    2023-05-05
 */
#include <bits/stdc++.h>

using i64 = long long;
using i64u = unsigned long long;
using f80 = long double;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  std::vector<int> nxt(n);
  for (int i = 0; i < n; i++) {
    std::cin >> nxt[i];
  }

  int pivot;
  std::cin >> pivot;

  while (pivot != 0) {
    std::cout << pivot << " ";
    pivot = nxt[pivot - 1];
  }
  std::cout << "\n";

  return 0;
}