/*
 * @file    P2079 烛光晚餐.cpp
 * @author  ForgotDream
 * @brief   Knapsack DP
 * @date    2024-01-10
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 105, M = 550;

int n, m, c[N], x[N], y[N];
int f[M][M];

void solve() {
  std::cin >> n >> m;
  int d = 0, tot = 0;
  for (int i = 1; i <= n; i++) {
    std::cin >> c[i] >> x[i] >> y[i];
    if (x[i] < 0) d -= x[i];
    else tot += x[i];
  }

  memset(f, -0x3f, sizeof(f)), f[0][d] = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = m; j >= c[i]; j--) {
      if (x[i] > 0) {
        for (int k = tot + d; k >= x[i]; k--) {
          f[j][k] = std::max(f[j][k], f[j - c[i]][k - x[i]] + y[i]);
        }
      } else {
        for (int k = 0; k <= tot + d; k++) {
          f[j][k] = std::max(f[j][k], f[j - c[i]][k - x[i]] + y[i]);
        }
      }
    }
  }

  int ans = -1;
  for (int i = 0; i <= m; i++) {
    for (int j = d; j <= tot + d; j++) {
      ans = std::max(ans, f[i][j]);
      if (f[i][j] >= -1e9) std::cerr << j - d << "\n";
    }
  }
  std::cout << ans << "\n";
}

signed main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
