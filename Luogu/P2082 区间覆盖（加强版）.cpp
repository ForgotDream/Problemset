/**
 * @file    P2082 区间覆盖（加强版）.cpp
 * @author  ForgotDream
 * @brief   Greedy
 * @date    2023-08-07
 */
#include <bits/stdc++.h>
using i64 = long long;
using pll = std::pair<i64, i64>;
constexpr int N = 1e5 + 50;
int n;
pll a[N];
i64 ans;
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i].first >> a[i].second;
  std::sort(a + 1, a + n + 1);
  int lp = a[1].first, rp = a[1].second;
  ans = rp - lp + 1;
  for (int i = 2; i <= n; i++) {
    auto [l, r] = a[i];
    if (l > rp) lp = l, rp = r, ans += r - l + 1;
    else if (r > rp) ans += r - rp, rp = r;
  }
  std::cout << ans << "\n";
  return 0;
}