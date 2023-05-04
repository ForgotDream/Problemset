/**
 * @file    P2627 Mowing the Lawn G.cpp
 * @author  ForgotDream
 * @brief   Monotone Queue + DP
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

  std::vector<i64> s(n + 1);
  for (int i = 1; i <= n; i++) {
    int c;
    std::cin >> c;
    s[i] = c + s[i - 1];
  }

  std::deque<int> dq;
  std::vector f(n + 1, std::vector<i64>(2, 0));
  dq.push_back(0);
  for (int i = 1; i <= n; i++) {
    f[i][0] = std::max(f[i - 1][0], f[i - 1][1]);
    while (!dq.empty() && dq.front() < i - k) {
      dq.pop_front();
    }
    f[i][1] = f[dq.front()][0] + s[i] - s[dq.front()];
    while (!dq.empty() && f[dq.back()][0] - s[dq.back()] < f[i][0] - s[i]) {
      dq.pop_back();
    }
    dq.push_back(i);
  }

  std::cout << std::max(f[n][0], f[n][1]) << "\n";

  return 0;
}