/*
 * @file    P2303 [SDOI2012] Longge 的问题.cpp
 * @author  ForgotDream
 * @brief   Math
 * @date    2024-01-31
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

u32 n;

void solve() {
  std::cin >> n;

  i64 ans = n;
  for (u32 i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      int ct = 0;
      while (n % i == 0) n /= i, ct++;
      ans /= i;
      ans *= 1ll * ct * i - ct + i;
    }
  }
  if (n > 1) ans /= n, ans *= 2ll * n - 1;

  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
