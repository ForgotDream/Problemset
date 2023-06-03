/**
 * @file    P2866 Bad Hair Day S.cpp
 * @author  ForgotDream
 * @brief   Monotone Stack
 * @date    2023-05-26
 */
#include <bits/stdc++.h>

using i64 = long long;

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
  i64 ans = 0;
  for (int i = 0; i < n; i++) {
    while (!s.empty() && a[s.top()] <= a[i]) {
      s.pop();
    }
    ans += s.size();
    s.push(i);
  }

  std::cout << ans << "\n";

  return 0;
}