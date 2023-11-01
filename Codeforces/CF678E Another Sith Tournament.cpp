/**
 * @file    CF678E Another Sith Tournament.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-10-31
 */
#include <iostream>
#include <iomanip>

using i64 = long long;
using f80 = long double;

constexpr int N = 18;
int n;
f80 a[N][N], f[1 << N][N];
void solve() {
  std::cin >> n;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) std::cin >> a[i][j];
  }
  int mask = (1 << n) - 1;
  f[1][0] = 1;
  for (int i = 2; i <= mask; i++) {
    for (int j = 0; j < n; j++) {
      if (!(i & (1 << j))) continue;
      for (int k = 0; k < n; k++) {
        if (!(i & (1 << k))) continue;
        if (j == k) continue;
        f[i][j] = std::max(f[i][j], f[i - (1 << j)][k] * a[k][j] +
                                        f[i - (1 << k)][j] * a[j][k]);
      }
    }
  }
  f80 ans = 0;
  for (int i = 0; i < n; i++) ans = std::max(ans, f[mask][i]);
  std::cout << std::fixed << std::setprecision(12) << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
