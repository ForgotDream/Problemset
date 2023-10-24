/**
 * @file    CF538B Quasi Binary.cpp
 * @author  ForgotDream
 * @brief   Ad Hoc
 * @date    2023-08-29
 */
#include <algorithm>
#include <iostream>
#include <iomanip>

using i64 = long long;

constexpr int pw[] = {1, 10, 100, 1000, 10000, 100000, 1000000};
int n;
int dig[10], n;
int ans[10];
void solve() {
  std::cin >> n;
  while (n) dig[++n] = n % 10, n /= 10;
  int cnt = *std::max_element(dig + 1, dig + n + 1);
  std::cout << cnt << "\n";
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= dig[i]; j++) ans[j] += pw[i - 1];
  }
  for (int i = 1; i <= cnt; i++) std::cout << ans[i] << " \n"[i == n];
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}