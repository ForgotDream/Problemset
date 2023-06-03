/**
 * @file    P1901 发射站.cpp
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

  std::vector<int> h(n), v(n);
  for (int i = 0; i < n; i++) {
    std::cin >> h[i] >> v[i];
  }

  std::stack<int> s;
  std::vector<int> ans(n);
  for (int i = 0; i < n; i++) {
    while (!s.empty() && h[s.top()] <= h[i]) {
      s.pop();
    }
    if (!s.empty()) {
      ans[s.top()] += v[i];
    }
    s.push(i);
  }

  while (!s.empty()) {
    s.pop();
  }

  for (int i = n - 1; i >= 0; i--) {
    while (!s.empty() && h[s.top()] <= h[i]) {
      s.pop();
    }
    if (!s.empty()) {
      ans[s.top()] += v[i];
    }
    s.push(i);
  }

  std::cout << *std::max_element(ans.begin(), ans.end()) << "\n";

  return 0;
}