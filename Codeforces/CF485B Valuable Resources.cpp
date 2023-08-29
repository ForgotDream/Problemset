/**
 * @file    CF485B Valuable Resources.cpp
 * @author  ForgotDream
 * @brief   shabi
 * @date    2023-08-24
 */
#include <algorithm>
#include <iostream>

using i64 = long long;

constexpr int N = 1050;
int n, x[N], y[N];
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> x[i] >> y[i];
  int h =
      *std::max_element(x + 1, x + n + 1) - *std::min_element(x + 1, x + n + 1);
  int w =
      *std::max_element(y + 1, y + n + 1) - *std::min_element(y + 1, y + n + 1);
  std::cout << 1ll * std::max(h, w) * std::max(h, w) << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}