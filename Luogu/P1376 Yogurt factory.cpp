/**
 * @file    P1376 Yogurt factory.cpp
 * @author  ForgotDream
 * @brief   Greedy
 * @date    2023-05-13
 */
#include <bits/stdc++.h>

using i64 = long long;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, s;
  std::cin >> n >> s;

  std::vector<int> c(n), y(n);
  for (int i = 0; i < n; i++) {
    std::cin >> c[i] >> y[i];
  }

  int d = INT_MAX;
  i64 ans = 0;
  for (int i = 0; i < n; i++) {
    d = std::min(d, c[i]);
    ans += 1ll * y[i] * d;
    d += s;
  }

  std::cout << ans << "\n";

  return 0;
}