/**
 * @file    CF1856C To Become Max.cpp
 * @author  ForgotDream
 * @brief   Binary Search
 * @date    2023-08-07
 */
#include <bits/stdc++.h>
using i64 = long long;
constexpr int N = 1050;
int t, n, k, a[N], max, ans;
bool check(int val) {
  i64 res = 1e9;
  for (int i = 1; i < n; i++) {
    int cur = val - 1;
    i64 cnt = val - a[i], j;
    for (j = i + 1; j < n; j++, cur--) {
      if (a[j] >= cur) break;
      else cnt += cur - a[j];
    }
    if (j == n && a[n] < cur) cnt = 1e9;
    res = std::min(res, cnt);
  }
  return res <= k;
}
void solve() {
  std::cin >> n >> k;
  max = 0;
  for (int i = 1; i <= n; i++) std::cin >> a[i], max = std::max(max, a[i]);
  int lo = max, hi = max + k;
  ans = max;
  while (lo <= hi) {
    int mid = (lo + hi) >> 1;
    if (check(mid)) lo = mid + 1, ans = mid;
    else hi = mid - 1;
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