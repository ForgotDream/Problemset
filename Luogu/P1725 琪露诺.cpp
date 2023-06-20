/**
 * @file    P1725 琪露诺.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-06-18
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int inf = 1e9;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, l, r;
  std::cin >> n >> l >> r;
  ++n;

  std::vector<int> a(n);
  for (int i = 0; i < n; i++) { std::cin >> a[i]; }

  std::vector<int> f(n, -inf);
  std::deque<int> dq;
  f[0] = 0, dq.push_back(0);
  for (int i = l; i < n; i++) {
    while (!dq.empty() && dq.front() < i - r) { dq.pop_front(); }
    f[i] = f[dq.front()] + a[i];
    while (!dq.empty() && f[dq.back()] < f[i - l + 1]) { dq.pop_back(); }
    dq.push_back(i - l + 1);
  }

  std::cout << *std::max_element(f.begin() + n - r, f.end()) << "\n";
  return 0;
}