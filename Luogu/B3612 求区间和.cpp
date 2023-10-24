/**
 * @file    B3612 求区间和.cpp
 * @author  ForgotDream
 * @brief   Prefix Sum
 * @date    2023-05-03
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

  std::vector<int> s(n);
  for (int i = 0; i < n; i++) {
    int c;
    std::cin >> c;
    s[i] = c + (i ? s[i - 1] : 0);
  }

  int m;
  std::cin >> m;

  while (m--) {
    int l, r;
    std::cin >> l >> r;
    l--, r--;
    std::cout << s[r] - (l ? s[l - 1] : 0) << "\n";
  }

  return 0;
}