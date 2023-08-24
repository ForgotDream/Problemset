/**
 * @file    CF1613C Poisoned Dagger.cpp
 * @author  ForgotDream
 * @brief   Binary Search
 * @date    2023-08-22
 */
#include <algorithm>
#include <iostream>

using i64 = long long;

constexpr int N = 2e5 + 50;
int t, n, a[N];
i64 h;

bool check(i64 val) {
  i64 res = 0;
  for (int i = 1; i < n; i++) {
    res += std::min(static_cast<i64>(a[i + 1] - a[i]), val);
  }
  res += val;
  return res >= h;
}

void solve() {
  std::cin >> n >> h;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  
  i64 lo = 0, hi = 1e18, ans = hi;
  while (lo <= hi) {
    i64 mid = (lo + hi) >> 1;
    if (check(mid)) hi = mid - 1, ans = mid;
    else lo = mid + 1;
  }
  std::cout << ans << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> t;

  while (t--) solve();

  return 0;
}