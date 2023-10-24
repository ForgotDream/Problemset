/**
 * @file    CF1613D MEX Sequences.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-08-22
 */
#include <algorithm>
#include <cstring>
#include <iostream>

using i64 = long long;

constexpr int N = 5e5 + 50, mod = 998244353;
int t, n;
i64 f[N][2], a[N];

void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i], a[i]++;
  
  f[0][0] = 1;
  for (int i = 1; i <= n; i++) {
    f[a[i]][0] = (2 * f[a[i]][0] + f[a[i] - 1][0]) % mod;
    f[a[i]][1] = 2 * f[a[i]][1] % mod;
    f[a[i] + 2][1] = 2 * f[a[i] + 2][1] % mod;
    if (a[i] > 1) (f[a[i]][1] += f[a[i] - 2][0]) %= mod;
  }

  i64 ans = 0;
  for (int i = 1; i <= n + 1; i++) {
    (ans += f[i][0]) %= mod;
    (ans += f[i][1]) %= mod;
    f[i][0] = f[i][1] = 0;
  }
  std::cout << ans << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> t;

  while (t--) solve();

  return 0;
}