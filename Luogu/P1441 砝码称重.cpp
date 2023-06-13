/**
 * @file    P1441 砝码称重.cpp
 * @author  ForgotDream
 * @brief   Brute Force
 * @date    2023-06-13
 */
#include <bits/stdc++.h>

using i64 = long long;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  std::vector<int> a(n);
  for (int i = 0; i < n; i++) { std::cin >> a[i]; }

  int ans = 0;
  for (int st = 0; st < (1 << n); st++) {
    if (__builtin_popcount(st) != n - m) { continue; }
    std::bitset<2001> bit;
    bit[0] = true;
    for (int i = 0; i < n; i++) {
      if (st & (1 << i)) { bit |= (bit << a[i]); }
    }
    ans = std::max(ans, int(bit.count()));
  }

  std::cout << ans - 1 << "\n";

  return 0;
}