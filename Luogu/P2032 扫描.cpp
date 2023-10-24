/**
 * @file    P2032 扫描.cpp
 * @author  ForgotDream
 * @brief   Monotone Queue
 * @date    2023-05-26
 */
#include <bits/stdc++.h>

using i64 = long long;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, k;
  std::cin >> n >> k;

  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  std::deque<int> dq;
  for (int i = 0; i < n; i++) {
    while (!dq.empty() && a[dq.back()] <= a[i]) {
      dq.pop_back();
    }
    dq.push_back(i);
    while (!dq.empty() && dq.front() + k <= i) {
      dq.pop_front();
    }
    if (i >= k - 1) {
      std::cout << a[dq.front()] << "\n";
    }
  }

  return 0;
}