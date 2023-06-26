/**
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2023-06-26
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 50;
int n, m, p;
int d[N], h[N], t[N], q[N];
i64 f[N];

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n >> m >> p;
  for (int i = 1; i <= n; i++) {
    std::cin >> d[i];
  }
  for (int i = 1; i <= m; i++) {
    std::cin >> h[i] >> t[i];
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j < i; j++) {
      f[i] = std::min(f[i], f[j]);
    }    
  }

  return 0;
}
