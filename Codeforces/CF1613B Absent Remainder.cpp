/**
 * @file    CF1613B Absent Remainder.cpp
 * @author  ForgotDream
 * @brief   shabi
 * @date    2023-08-22
 */
#include <algorithm>
#include <iostream>

using i64 = long long;

constexpr int N = 2e5 + 50;
int t, n, a[N];

void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  int min = *std::min_element(a + 1, a + n + 1);
  int cnt = 0;
  for (int i = 1; i <= n; i++) {
    if (a[i] != min) std::cout << a[i] << " " << min << "\n", cnt++;
    if (cnt == n / 2) break;
  }
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> t;

  while (t--) solve();

  return 0;
}