/**
 * @file    CF1753A2 Make Nonzero Sum (hard version).cpp
 * @author  ForgotDream
 * @brief   Ad Hoc
 * @date    2023-08-06
 */
#include <bits/stdc++.h>
using i64 = long long;
constexpr int N = 2e5 + 50;
int t, n, a[N], select[N], sum, ans;
void solve() {
  std::cin >> n;
  sum = 0, ans = n;
  for (int i = 1; i <= n; i++) std::cin >> a[i], select[i] = 0, sum += a[i];
  for (int i = 2; i <= n; i++) {
    if (std::abs(sum - 2 * a[i]) < std::abs(sum) && !select[i - 1]) {
      select[i] = 1, ans--, sum -= 2 * a[i];
    }
  }
  if (sum) return void(std::cout << -1 << "\n");
  std::cout << ans << "\n";
  select[n + 1] = 0;
  for (int i = 1; i <= n; i++) {
    if (select[i]) continue;
    if (select[i + 1]) std::cout << i << " " << i + 1 << "\n";
    else std::cout << i << " " << i << "\n";
  }
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> t;
  while (t--) solve();
  return 0;
}