/**
 * @file    P2947 Look Up S.cpp
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

  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  std::stack<int> s;
  std::vector<int> ans(n);
  for (int i = n - 1; i >= 0; i--) {
    while (!s.empty() && a[i] >= a[s.top()]) {
      s.pop();
    }
    if (s.empty()) {
      ans[i] = 0;
    } else {
      ans[i] = s.top() + 1;
    }
    s.push(i);
  }

  for (int i = 0; i < n; i++) {
    std::cout << ans[i] << "\n";
  }

  return 0;
}