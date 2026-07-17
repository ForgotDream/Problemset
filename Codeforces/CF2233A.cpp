/*
 * @file
 * @author  ForgotDream
 * @brief   
 * @date    2025-09-08
 */
#include <iostream>

using i64 = long long;

void solve() {
  int n, x, y, z;
  std::cin >> n >> x >> y >> z;

  int ans = (n - 1) / (x + y) + 1;

  if (n >= z * x) {
    n -= z * x;
    ans = std::min(ans, z + (n - 1) / (x + 10 * y) + 1);
  }

  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  std::cin >> t;
  while (t--) solve();

  return 0;
}
