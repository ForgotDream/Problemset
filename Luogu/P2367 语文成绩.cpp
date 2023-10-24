/**
 * @file    P2367 语文成绩.cpp
 * @author  ForgotDream
 * @brief   Differnece
 * @date    2023-05-03
 */
#include <bits/stdc++.h>

using i64 = long long;
using i64u = unsigned long long;
using f80 = long double;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, p;
  std::cin >> n >> p;

  std::vector<int> d(n), a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
    d[i] = a[i] - (i ? a[i - 1] : 0);
  }

  while (p--) {
    int l, r, delta;
    std::cin >> l >> r >> delta;
    l--, r--;
    d[l] += delta;
    if (r != n - 1) {
      d[r + 1] -= delta;
    }
  }

  int min = INT_MAX, cur = 0;
  for (int i = 0; i < n; i++) {
    cur += d[i];
    min = std::min(min, cur);
  }

  std::cout << min << "\n";

  return 0;
}