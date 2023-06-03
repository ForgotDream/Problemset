/**
 * @file    P1714 切蛋糕.cpp
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

  std::partial_sum(a.begin(), a.end(), a.begin());

  std::deque<int> dq;
  dq.push_back(-1);
  int ans = INT_MIN;
  for (int i = 0; i < n; i++) {
    while (!dq.empty() && dq.front() + m < i) {
      dq.pop_front();
    }
    if (dq.front() == -1) {
      ans = std::max(ans, a[i]);
    } else {
      ans = std::max(ans, a[i] - a[dq.front()]);
    }
    while (!dq.empty() && a[dq.back()] >= a[i]) {
      dq.pop_back();
    }
    dq.push_back(i);
  }

  std::cout << ans << "\n";

  return 0;
}