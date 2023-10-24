/**
 * @file    CF255D Mr. Bender and Square.cpp
 * @author  ForgotDream
 * @brief   shabi
 * @date    2023-08-15
 */
#include <bits/stdc++.h>
using i64 = long long;
i64 n, x, y, c;
bool check(i64 val) {
  i64 s = 2 * val * val + 2 * val + 1;
  if (val - x > 0) s -= (val - x) * (val - x);
  if (val - (n - 1 - x) > 0) s -= (val - (n - 1 - x)) * (val - (n - 1 - x));
  if (val - y > 0) s -= (val - y) * (val - y);
  if (val - (n - 1 - y) > 0) s -= (val - (n - 1 - y)) * (val - (n - 1 - y));
  if (val - x - (n - y - 1) - 1 > 0)
    s += (1 + val - x - (n - y - 1) - 1) * (val - x - (n - y - 1) - 1) / 2;
  if (val - (n - 1 - x) - (n - 1 - y) > 0)
    s += (1 + val - (n - 1 - x) - (n - 1 - y) - 1) *
         (val - (n - 1 - x) - (n - 1 - y) - 1) / 2;
  if (val - (n - 1 - x) - y - 1 > 0)
    s += (1 + val - (n - 1 - x) - y - 1) * (val - (n - 1 - x) - y - 1) / 2;
  if (val - y - x - 1 > 0)
    s += (1 + val - y - x - 1) * (val - y - x - 1) / 2;
  return s >= c;
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n >> x >> y >> c;
  x--, y--;
  i64 lo = 0, hi = 2 * n, ans = hi + 1;
  while (lo <= hi) {
    i64 mid = (lo + hi) >> 1;
    if (check(mid)) hi = mid - 1, ans = std::min(ans, mid);
    else lo = mid + 1;
  }
  std::cout << ans << "\n";
  return 0;
}