/*
 * @file    P2113 看球泡妹子.cpp
 * @author  ForgotDream
 * @brief   Knapsack DP
 * @date    2024-01-10
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 105, M = 2050;

int n, m, k, c, a[N], b[N];

int f[N][M];

void solve() {
  std::cin >> n >> m >> k >> c;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  for (int i = 1; i <= n; i++) std::cin >> b[i];

  memset(f, -0x3f, sizeof(f)), f[0][0] = 0;
  for (int i = 1, p, q; i <= m; i++) {
    std::cin >> p >> q;
    for (int j = std::min(i, k); j; j--) {
      for (int l = M - 1; l >= b[p] + b[q]; l--) {
        f[j][l] = std::max(f[j][l], f[j - 1][l - b[p] - b[q]] + a[p] * a[q]);
      }
    }
  }

  int ans = -1;
  for (int i = c; i < M; i++) ans = std::max(ans, f[k][i]);
  std::cout << ans << "\n";
}

signed main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
