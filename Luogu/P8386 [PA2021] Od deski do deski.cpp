/*
 * @file    P8386 [PA2021] Od deski do deski.cpp
 * @author  ForgotDream
 * @brief   DP / DP of DP
 * @date    2024-02-14
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 3050, mod = 1e9 + 7;

int n, m;

i64 f[N][N][2];

void solve() {
  std::cin >> n >> m;

  f[0][0][1] = 1;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j <= i; j++) {
      (f[i + 1][j][1] += j * f[i][j][1] % mod) %= mod;
      (f[i + 1][j + 1][0] += (m - j) * f[i][j][1] % mod) %= mod;
      (f[i + 1][j][1] += j * f[i][j][0] % mod) %= mod;
      (f[i + 1][j][0] += (m - j) * f[i][j][0] % mod) %= mod;
    }
  }

  i64 ans = 0;
  for (int i = 0; i <= n; i++) ans += f[n][i][1];
  std::cout << ans % mod << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
