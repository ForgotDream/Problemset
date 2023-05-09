/**
 * @file    P4306 连通数.cpp
 * @author  ForgotDream
 * @brief   Transitive Closure
 * @date    2023-05-09
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2000;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int n;
  std::cin >> n;

  std::vector<std::bitset<N>> a(n);
  for (int i = 0; i < n; i++) {
    a[i][i] = true;
    for (int j = 0; j < n; j++) {
      char c;
      std::cin >> c;
      if (c == '1') {
        a[i][j] = true;
      }
    }
  }

  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      if (a[i][k]) {
        a[i] = a[i] | a[k];
      }
    }
  }

  int ans = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      ans += a[i][j];
    }
  }

  std::cout << ans << "\n";

  return 0;
}