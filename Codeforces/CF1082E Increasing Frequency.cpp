/**
 * @file    CF1082E Increasing Frequency.cpp
 * @author  ForgotDream
 * @brief   贪心
 * @date    2023-03-19
 */
#include <bits/stdc++.h>

using i64 = long long;
using f80 = long double;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  static const int MAXX = 6e5 + 50;

  int n, k;
  std::cin >> n >> k;

  std::vector<int> a(MAXX), b(MAXX);

  int cnt = 0, ans = 0;
  for (int i = 0; i < n; i++) {
    int num;
    std::cin >> num;
    if (num == k) {
      cnt++;
    } else {
      if (a[num] && a[num] + b[num] - cnt >= 0) {
        a[num] += b[num] - cnt;
      } else {
        a[num] = 0;
      }
      a[num]++;
      b[num] = cnt;
      ans = std::max(ans, a[num]);
    }
  }
  std::cout << ans + cnt << "\n";

  return 0;
}