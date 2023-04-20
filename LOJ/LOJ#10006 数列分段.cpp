/**
 * @file    LOJ#10006 数列分段.cpp
 * @author  ForgotDream
 * @brief   贪心
 * @date    2023-03-20
 */
#include <bits/stdc++.h>

using i64 = long long;
using f80 = long double;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  int pivot = 0, cur = 0, ans = 0;
  while (pivot < n) {
    cur += a[pivot];
    if (cur > m) {
      ans++;
      cur = a[pivot];
    }
    pivot++;
  }

  std::cout << ans + 1 << "\n";

  return 0;
}