/**
 * @file    CF1829H Don't Blame Me.cpp
 * @author  ForgotDream
 * @brief   DP + Bitwise
 * @date    2023-05-08
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int MOD = 1e9 + 7;

void solve() {
  int n, k;
  std::cin >> n >> k;

  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  std::vector f(n, std::vector<int>(1 << 6));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < (1 << 6); j++) {
      (f[i][j] += (i ? f[i - 1][j] : 0)) %= MOD;
      (f[i][j & a[i]] += (i ? f[i - 1][j] : 0)) %= MOD;
    }
    (f[i][a[i]] += 1) %= MOD;
  }

  int ans = 0;
  for (int i = 0; i < (1 << 6); i++) {
    if (__builtin_popcount(i) == k) {
      (ans += f[n - 1][i]) %= MOD;
    }
  }

  std::cout << ans << "\n";

  return;
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  std::cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}