/**
 * @file    CF1753A1 Make Nonzero Sum (easy version).cpp
 * @author  ForgotDream
 * @brief   Ad Hoc
 * @date    2023-08-06
 */
#include <bits/stdc++.h>
using i64 = long long;
constexpr int N = 2e5 + 50;
int t, n, a[N];
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  if (n & 1) return void(std::cout << -1 << "\n");
  std::vector<std::pair<int, int>> ans;
  for (int i = 1; i <= n; i += 2) {
    if (a[i] == a[i + 1]) ans.emplace_back(i, i + 1);
    else ans.emplace_back(i, i), ans.emplace_back(i + 1, i + 1);
  }
  std::cout << ans.size() << "\n";
  for (auto [l, r] : ans) std::cout << l << " " << r << "\n";
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> t;
  while (t--) solve();
  return 0;
}