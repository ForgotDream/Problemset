/*
 * @file    AT_agc013_d [AGC013D] Piling Up.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2024-02-12
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 3050, mod = 1e9 + 7;

int n, m;
i64 f[N][N][2];

void solve() {
  std::cin >> n >> m;

  for (int i = 0; i <= n; i++) f[0][i][i == 0] = 1;

  for (int i = 0; i < m; i++) {
    for (int j = 0; j <= n; j++) {
      for (int k = 0; k < 2; k++) {
        if (j > 0) {
          (f[i + 1][j][k | (j == 1)] += f[i][j][k]) %= mod;
          (f[i + 1][j - 1][k | (j == 1)] += f[i][j][k]) %= mod;
        }
        if (j < n) {
          (f[i + 1][j][k] += f[i][j][k]) %= mod;
          (f[i + 1][j + 1][k] += f[i][j][k]) %= mod;
        }
      }
    }
  }

  i64 ans = 0;
  for (int i = 0; i <= n; i++) (ans += f[m][i][1]) %= mod;
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
