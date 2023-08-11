/**
 * @file    P3166 [CQOI2014] 数三角形.cpp
 * @author  ForgotDream
 * @brief   Math
 * @date    2023-08-10
 */
#include <bits/stdc++.h>
using i64 = long long;
int n, m;
i64 C3(i64 n) { return 1ll * n * (n - 1) * (n - 2) / 6;  }
i64 ans = 0;
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n >> m;
  ans = C3((n + 1) * (m + 1));
  ans -= (n + 1) * C3(m + 1) + (m + 1) * C3(n + 1);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      ans -= 2ll * (m - j + 1) * (n - i + 1) * (std::__gcd(i, j) - 1);
    }
  }
  std::cout << ans << "\n";
  return 0;
}