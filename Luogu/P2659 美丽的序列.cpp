/**
 * @file    P2659 美丽的序列.cpp
 * @author  ForgotDream
 * @brief   Monotone Stack
 * @date    2023-05-26
 */
#include <bits/stdc++.h>

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  
  int n;
  std::cin >> n;

  std::vector<i64> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  std::stack<int> s;
  std::vector<i64> width(n);
  for (int i = 0; i < n; i++) {
    while (!s.empty() && a[s.top()] >= a[i]) {
      s.pop();
    }
    if (s.empty()) {
      width[i] = i + 1;
    } else {
      width[i] = i - s.top();
    }
    s.push(i);
  }

  while (!s.empty()) {
    s.pop();
  }

  for (int i = n - 1; i >= 0; i--) {
    while (!s.empty() && a[s.top()] >= a[i]) {
      s.pop();
    }
    if (s.empty()) {
      width[i] += n - i - 1;
    } else {
      width[i] += s.top() - i - 1;
    }
    s.push(i);
  }

  i64 ans = 0;
  for (int i = 0; i < n; i++) {
    ans = std::max(ans, a[i] * width[i]);
  }

  std::cout << ans << "\n";

  return 0;
}