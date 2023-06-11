/**
 * @file    P3622 动物园.cpp
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

  int n, c;
  std::cin >> n >> c;

  std::vector num(n, std::vector<int>(1 << 5));
  for (int i = 0; i < c; i++) {
    int e, f, l;
    std::cin >> e >> f >> l;
    int fst = 0, lst = 0;
    for (int j = 0; j < f; j++) { 
      int val;
      std::cin >> val;
      val = (val - e + n) % n, fst |= 1 << val;
    }
    for (int j = 0; j < l; j++) { 
      int val;
      std::cin >> val;
      val = (val - e + n) % n, lst |= 1 << val;
    }
    for (int j = 0; j < (1 << 5); j++) {
      if (fst & (~j) || lst & j) { num[e - 1][j]++; }
    }
  }

  std::vector f(n, std::vector<int>(1 << 5));
  int ans = -inf;
  for (int i = 0; i < (1 << 5); i++) {
    f[0].assign(1 << 5, -inf);
    for (int st = 0; st < (1 << 5); st++) {
      int lst = (st & 15) << 1, rst = (st & 15) << 1 | 1;
      if (lst == i || rst == i) { f[0][st] = 0; }
      f[0][st] += num[0][st];
    }
    for (int j = 1; j < n; j++) {
      for (int st = 0; st < (1 << 5); st++) {
        int lst = (st & 15) << 1, rst = (st & 15) << 1 | 1;
        f[j][st] = std::max(f[j - 1][lst], f[j - 1][rst]) + num[j][st];
      }
    }
    ans = std::max(ans, f[n - 1][i]);
  }

  std::cout << ans << "\n";

  return 0;
}