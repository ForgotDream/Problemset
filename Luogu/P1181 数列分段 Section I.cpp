/**
 * @file    P1181 数列分段 Section I.cpp
 * @author  ForgotDream
 * @brief   Greedy
 * @date    2023-06-07
 */
#include <bits/stdc++.h>

using i64 = long long;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  std::vector<int> a(n);
  for (int i = 0; i < n; i++) { std::cin >> a[i]; }

  int cur = 0, ans = 1;
  for (int i = 0; i < n; i++) {
    cur += a[i];
    if (cur > m) { ans++, cur = a[i]; }
  }

  std::cout << ans << "\n";

  return 0;
}