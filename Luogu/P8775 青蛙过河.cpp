/**
 * @file    P8775 青蛙过河.cpp
 * @author  ForgotDream
 * @brief   Two Pointers
 * @date    2023-05-04
 */
#include <bits/stdc++.h>

using i64 = long long;
using i64u = unsigned long long;
using f80 = long double;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, x;
  std::cin >> n >> x;
  x *= 2;

  std::vector<int> h(n);
  for (int i = 0; i < n - 1; i++) {
    std::cin >> h[i];
  }

  int ans = 0;
  for (int i = 0, j = -1, sum = 0; i < n - 1; i++) {
    while (j < n - 1 && sum < x) {
      j++;
      sum += h[j];
    }
    ans = std::max(ans, j - i + 1);
    sum -= h[i];
  }

  std::cout << ans << "\n";

  return 0;
}