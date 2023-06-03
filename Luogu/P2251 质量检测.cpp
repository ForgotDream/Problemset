/**
 * @file    P2251 质量检测.cpp
 * @author  ForgotDream
 * @brief   Monotone Queue
 * @date    2023-05-26
 */
#include <bits/stdc++.h>

using i64 = long long;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  std::deque<int> dq;
  for (int i = 0; i < n; i++) {
    while (!dq.empty() && a[dq.back()] >= a[i]) {
      dq.pop_back();
    }
    dq.push_back(i);
    while (!dq.empty() && dq.front() + m <= i) {
      dq.pop_front();
    }
    if (i >= m - 1) {
      std::cout << a[dq.front()] << "\n";
    }
  }

  return 0;
}