/**
 * @file    P2397 yyy loves Maths VI (mode).cpp
 * @author  ForgotDream
 * @brief   Moore Vote
 * @date    2023-05-08
 */
#include <bits/stdc++.h>

using i64 = long long;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  int cur = 0, cnt = 0;
  for (int i = 1; i <= n; i++) {
    int c;
    std::cin >> c;
    if (!cnt) {
      cur = c, cnt++;
    }
    if (cur == c) {
      cnt++;
    } else {
      cnt--;
    }
  }

  std::cout << cur << "\n";

  return 0;
}