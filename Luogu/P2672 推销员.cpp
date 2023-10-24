/**
 * @file    P2672 推销员.cpp
 * @author  ForgotDream
 * @brief   Greedy
 * @date    2023-05-13
 */
#include <bits/stdc++.h>

using i64 = long long;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  std::vector<std::pair<int, int>> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i].second;
  }
  for (int i = 0; i < n; i++) {
    std::cin >> a[i].first;
  }

  std::sort(a.begin(), a.end(), std::greater<std::pair<int, int>>());

  std::vector<int> sum(n), f(n), g(n);
  for (int i = 0; i < n; i++) {
    sum[i] = a[i].first + (i ? sum[i - 1] : 0);
  }
  for (int i = 0; i < n; i++) {
    f[i] = std::max((i ? f[i - 1] : 0), 2 * a[i].second);
  }
  for (int i = n - 1; ~i; i--) {
    g[i] = std::max((n - i - 1 ? g[i + 1] : 0), 2 * a[i].second + a[i].first);
  }

  for (int i = 0; i < n; i++) {
    std::cout << std::max(sum[i] + f[i],  (i ? sum[i - 1] : 0) + g[i]) << "\n";
  }

  return 0;
}