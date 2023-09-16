/**
 * @file    CF1618D Array and Operations.cpp
 * @author  ForgotDream
 * @brief   Greedy
 * @date    2023-09-08
 */
#include <algorithm>
#include <iostream>

using i64 = long long;

constexpr int N = 2e5 + 50;
int n, k, a[N];
void solve() {
  std::cin >> n >> k;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  std::sort(a + 1, a + n + 1, std::greater<>());
  int ans = 0;
  for (int i = 1; i <= k; i++) ans += (a[i + k] == a[i]);
  for (int i = 2 * k + 1; i <= n; i++) ans += a[i];
  std::cout << ans << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}