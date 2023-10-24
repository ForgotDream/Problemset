/**
 * @file    P2473 [SCOI2008] 奖励关.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-09-23
 */
#include <iostream>
#include <iomanip>

using i64 = long long;
using f80 = long double;

constexpr int N = 16, M = 105;
int k, n, a[N], p[N];
f80 f[M][1 << N];
void solve() {
  std::cin >> k >> n;
  for (int i = 1, u; i <= n; i++) {
    std::cin >> a[i];
    while (std::cin >> u && u) p[i] |= (1 << (u - 1));
  }
  int mask = (1 << n) - 1;
  for (int i = k - 1; ~i; i--) {
    for (int j = 0; j <= mask; j++) {
      // if (__builtin_popcount(j) > i) continue;
      for (int l = 1; l <= n; l++) {
        if ((j & p[l]) == p[l]) {
          int p = j | (1 << (l - 1));
          f[i][j] += std::max(f[i + 1][p] + a[l], f[i + 1][j]);
        } else {
          f[i][j] += f[i + 1][j];
        }
      }
      f[i][j] /= n;
    }
  }
  std::cout << std::fixed << std::setprecision(6) << f[0][0] << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
