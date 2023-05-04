/**
 * @file    B3667 求区间所有后缀最大值的位置.cpp
 * @author  ForgotDream
 * @brief   Monotune Queue
 * @date    2023-05-04
 */
#include <bits/stdc++.h>

using i64 = long long;
using i64u = unsigned long long;
using f80 = long double;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, k;
  std::cin >> n >> k;

  std::vector<i64u> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  std::deque<int> dq;
  for (int i = 0; i < n; i++) {
    if (!dq.empty() && dq.front() + k <= i) {
      dq.pop_front();
    }
    while (!dq.empty() && a[dq.back()] <= a[i]) {
      dq.pop_back();
    }
    dq.push_back(i);
    if (i >= k - 1) {
      std::cout << dq.size() << "\n"; 
    }
  }

  return 0;
}