/**
 * @file    P1858 多人背包.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-06-11
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int inf = 1e9;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int k, v, n;
  std::cin >> k >> v >> n;

  std::vector<int> c(n), w(n);
  for (int i = 0; i < n; i++) { std::cin >> c[i] >> w[i]; }

  std::vector f(2, std::vector(v + 1, std::vector<int>(k, -inf)));
  int cnt = 0;
  f[cnt ^ 1][0][0] = 0;
  for (int i = 0; i < n; i++) {
    for (int j = v; j >= c[i]; j--) {
      int p1 = 0, p2 = 0;
      for (int p = 0; p < k; p++) {
        assert(p1 < k && p2 < k);
        assert((cnt ^ 1) < 2 && j <= v);
        if (f[cnt ^ 1][j][p1] > f[cnt ^ 1][j - c[i]][p2] + w[i]) {
          f[cnt][j][p] = f[cnt ^ 1][j][p1++];
        } else {
          f[cnt][j][p] = f[cnt ^ 1][j - c[i]][p2++] + w[i];
        }
      }
    }
    for (int j = c[i] - 1; j >= 0; j--) {
      for (int p = 0; p < k; p++) { f[cnt][j][p] = f[cnt ^ 1][j][p]; }
    }
    cnt ^= 1;
  }

  int ans = std::accumulate(f[cnt ^ 1][v].begin(), f[cnt ^ 1][v].end(), 0);
  std::cout << ans << "\n";

  return 0;
}