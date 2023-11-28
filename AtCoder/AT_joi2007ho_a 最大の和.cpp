/**
 * @file    AT_joi2007ho_a 最大の和.cpp
 * @author  ForgotDream
 * @brief   Shabi
 * @date    2023-11-27
 */
#include <bits/stdc++.h>

using i64 = int64_t;

constexpr int N = 1e5 + 50;
int n, k, a[N];
void solve() {
  std::cin >> n >> k;
  i64 ans = -1e18, cur = 0;
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i];
    if (i >= k) ans = std::max(ans, cur), cur -= a[i - k];
    cur += a[i];
  }
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
