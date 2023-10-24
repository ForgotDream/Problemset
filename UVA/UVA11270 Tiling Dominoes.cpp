/**
 * @file    UVA11270 Tiling Dominoes.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-06-12
 */
#include <bits/stdc++.h>

using i64 = long long;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  while (std::cin >> n >> m) {
    if (n < m) { std::swap(n, m); }
    int cur = 0;
    std::vector<std::vector<i64>> f(2, std::vector<i64>(1 << m));
    f[cur][(1 << m) - 1] = 1;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        cur ^= 1;
        std::fill(f[cur].begin(), f[cur].end(), 0);
        // st >> 1 舍弃最高位
        // 第一行该如何转移？
        for (int st = 0; st < (1 << m); st++) {
          int nxt = st << 1;
          if (nxt & (1 << m)) {
            f[cur][nxt ^ (1 << m)] += f[cur ^ 1][st];
          }
          if (i && !(st & (1 << (m - 1))) && ((nxt ^ (1 << m) ^ 1) & (1 << m))) {
            f[cur][(nxt ^ (1 << m) ^ 1) ^ (1 << m)] += f[cur ^ 1][st];
          }
          if (j && !(st & 1) && ((nxt ^ 3) & (1 << m))) {
            f[cur][(nxt ^ 3) ^ (1 << m)] += f[cur ^ 1][st];
          }
        }
      }
    }
    std::cout << f[cur][(1 << m) - 1] << "\n";
  }

  return 0;
}