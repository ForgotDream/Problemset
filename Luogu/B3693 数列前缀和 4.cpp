/**
 * @file    B3693 数列前缀和 4.cpp
 * @author  ForgotDream
 * @brief   2D Prefix Sum
 * @date    2023-05-03
 */
#include <bits/stdc++.h>

using i64 = long long;
using i64u = unsigned long long;
using f80 = long double;

void solve() {
  int n, m, q;
  std::cin >> n >> m >> q;

  std::vector s(n + 1, std::vector<i64u>(m + 1));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      i64u c;
      std::cin >> c;
      s[i][j] = c + s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
    }
  }

  i64u ans = 0;
  while (q--) {
    int u, v, x, y;
    std::cin >> u >> v >> x >> y;
    ans ^= s[x][y] - s[x][v - 1] - s[u - 1][y] + s[u - 1][v - 1];
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