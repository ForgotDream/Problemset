/**
 * @file
 * @author  ForgotDream
 * @brief
 * @date    2023-10-13
 */
#include <iostream>

using i64 = long long;

void solve() {
  int a;
  char c;
  int b;
  std::cin >> a >> c >> b;
  std::cout << a << " " << c << " " << b << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
