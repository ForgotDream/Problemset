/**
 * @file    P2114\ \[NOI2014\]\ 起床困难综合症.cpp
 * @author  ForgotDream
 * @brief   Ad Hoc + Greedy
 * @date    2023-11-04
 */
#include <iostream>

using i64 = long long;

constexpr int N = 1e5 + 50;
int n, m;
char s[10];
void solve() {
  std::cin >> n >> m;
  int a0 = 0, a1 = -1;
  for (int i = 1, val; i <= n; i++) {
    std::cin >> s >> val;
    if (s[0] == 'A') a0 &= val, a1 &= val;
    if (s[0] == 'O') a0 |= val, a1 |= val;
    if (s[0] == 'X') a0 ^= val, a1 ^= val;
  }
  int ans = 0;
  for (int i = 29; ~i; i--) {
    if (a0 & (1 << i)) ans += 1 << i;
    else if (a1 & (1 << i) && m >= (1 << i)) ans += 1 << i, m -= 1 << i;
  }
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
