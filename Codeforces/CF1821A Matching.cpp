/**
 * @file    CF1821A Matching.cpp
 * @author  ForgotDream
 * @brief   Simulation
 * @date    2023-05-09
 */
#include <bits/stdc++.h>

using i64 = long long;

void solve() {
  std::string s;
  std::cin >> s;

  if (s[0] == '0') {
    std::cout << 0 << "\n";
    return;
  }

  int ans = 1;
  for (int i = 0; i < s.length(); i++) {
    if (s[i] == '?') {
      ans *= 10 - (i == 0);
    }
  }

  std::cout << ans << "\n";

  return;
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int t;
  std::cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}