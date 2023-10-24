/**
 * @file    CF411C Kicker.cpp
 * @author  ForgotDream
 * @brief   shabi
 * @date    2023-08-29
 */
#include <iostream>

using i64 = long long;

int a[2], b[2], c[2], d[2];
void solve() {
  std::cin >> a[0] >> a[1] >> b[0] >> b[1] >> c[0] >> c[1] >> d[0] >> d[1];
  if ((a[0] > c[1] && a[0] > d[1] && b[1] > c[0] && b[1] > d[0]) ||
      (b[0] > c[1] && b[0] > d[1] && a[1] > c[0] && a[1] > d[0])) {
    std::cout << "Team 1\n";
    return;
  }
  if (((c[1] > a[0] && d[0] > b[1]) || (d[1] > a[0] && c[0] > b[1])) &&
      ((c[1] > b[0] && d[0] > a[1]) || (d[1] > b[0] && c[0] > a[1]))) {
    std::cout << "Team 2\n";
    return;
  }
  std::cout << "Draw\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}