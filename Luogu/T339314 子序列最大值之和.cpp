/**
 * @file    T339314 子序列最大值之和.cpp
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

  std::vector<int> l(n), r(n);
  std::stack<int> s;
  for (int i = 0; i < n; i++) {
    while (!s.empty() && a[s.top()] <= a[i]) {
      s.pop();
    }
    if (s.empty()) {
      l[i] = i + 1;
    } else {
      l[i] = i - s.top();
    }
    s.push(i);
  }
  while (!s.empty()) {
    s.pop();
  }
  for (int i = n - 1; i >= 0; i--) {
    while (!s.empty() && a[s.top()] < a[i]) {
      s.pop();
    }
    if (s.empty()) {
      r[i] = n - i;
    } else {
      r[i] = s.top() - i;
    }
    s.push(i);
  }

  i64 ans = 0;
  for (int i = 0; i < n; i++) {
    ans += 1ll * l[i] * r[i] * a[i];
  }

  std::cout << ans << "\n";

  return 0;
}