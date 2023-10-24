/**
 * @file    B3666 求数列所有后缀最大值的位置.cpp
 * @author  ForgotDream
 * @brief   Monotone Stack
 * @date    2023-05-04
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

  std::vector<i64u> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  int ans = 0;
  std::stack<int> s;
  for (int i = 0; i < n; i++) {
    while (!s.empty() && a[s.top()] < a[i]) {
      ans ^= (s.top() + 1);
      s.pop();
    }
    s.push(i);
    ans ^= (i + 1);
    std::cout << ans << "\n";
  }

  return 0;
}