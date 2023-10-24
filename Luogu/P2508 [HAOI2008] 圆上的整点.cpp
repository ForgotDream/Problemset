/**
 * @file    P2508 [HAOI2008] 圆上的整点.cpp
 * @author  ForgotDream
 * @brief   Math
 * @date    2023-10-21
 */
#include <iostream>

using i64 = long long;

int r;
i64 ans = 1;
void solve() {
  std::cin >> r;
  for (int i = 2; i * i <= r; i++) {
    if (r % i == 0) {
      int cnt = 0;
      while (r % i == 0) cnt++, r /= i;
      if (i % 4 == 1) ans *= 2 * cnt + 1;
    }
  }
  if (r != 1 && r % 4 == 1) ans *= 3;
  std::cout << 4 * ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
