/**
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2023-11-13
 */
#include <bits/stdc++.h>

using i64 = int64_t;

constexpr int N = 35, M = 13, mod = 998244353;
int n, m, k, a[N];
i64 f[N][M][1 << M];
void solve() {
  std::cin >> n >> m >> k;
  for (int i = 0; i <= m; i++) std::cin >> a[i];
  int mask = (1 << (m + 1)) - 1;
  f[0][0][0] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= m; j++) {
      for (int k = 1 << j; k <= mask; k++) {
        for (int l = 0; l <= j; l++) {
          // std::cout << f[i - 1][l][k - (1 << j)] << "\n";
          f[i][j][k] = 
              (f[i][j][k] + a[j] * f[i - 1][l][k - (1 << j)] % mod) % mod;
        }
      }
    }
  }
  i64 ans = 0;
  for (int i = 0; i <= m; i++) {
    for (int j = 0; j <= mask; j++) {
      if (__builtin_popcount(j) > k) continue;
      (ans += f[n][i][j]) %= mod;
    }
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
