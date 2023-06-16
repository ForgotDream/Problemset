/**
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2023-06-15
 */
#include <bits/stdc++.h>

using i64 = long long;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  std::vector a(n, std::vector<int>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) { std::cin >> a[i][j]; }
  }

  return 0;
}