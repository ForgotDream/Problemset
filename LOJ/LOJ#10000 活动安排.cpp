/**
 * @file    LOJ#10000 活动安排.cpp
 * @author  ForgotDream
 * @brief   贪心
 * @date    2023-03-17
 */
#include <bits/stdc++.h>

using i64 = long long;
using f80 = long double;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  std::vector<std::pair<int, int>> a(n);
  for (auto &i : a) {
    std::cin >> i.second >> i.first;
  }

  std::sort(a.begin(), a.end());

  int pivot = 0, ans = 0;
  for (int i = 0; i < n; i++) {
    if (a[i].second >= pivot) {
      ans++;
      pivot = a[i].first;
    }
  }

  std::cout << ans << "\n";

  return 0;
}