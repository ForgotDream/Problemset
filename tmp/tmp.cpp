/**
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2023-06-23
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int inf = 1e9;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int k, e, n;
  std::cin >> k >> e >> n;

  std::vector<int> x(n), f(n), c(n);
  for (int i = 0; i < n; i++) {
    std::cin >> x[i] >> f[i] >> c[i];
  }

  std::vector dp(n, std::vector<int>(k, inf));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < i; j++) {
      
    }
  }

  return 0;
}
