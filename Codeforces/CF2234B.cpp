/*
 * @file
 * @author  ForgotDream
 * @brief   
 * @date    2025-09-08
 */
#include <iostream>

using i64 = long long;

void solve() {
  i64 n;
  std::cin >> n;

  i64 rst = n % 12;
  if (rst != 10) {
    std::cout << rst << " " << n - rst << "\n";
  } else if (n >= 22) {
    std::cout << 22 << " " << n - 22 << "\n";
  } else {
    std::cout << -1 << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  std::cin >> t;
  while (t--) solve();

  return 0;
}
