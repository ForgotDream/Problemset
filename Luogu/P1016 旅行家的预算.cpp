/**
 * @file    P1016 旅行家的预算.cpp
 * @author  ForgotDream
 * @brief   DFS
 * @date    2023-05-13
 */
#include <bits/stdc++.h>

using i64 = long long;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout << std::fixed << std::setprecision(2);

  double d1, c, d2, p1;
  int n;
  std::cin >> d1 >> c >> d2 >> p1 >> n;

  std::vector<double> d(n + 2), p(n + 2);
  for (int i = 1; i <= n; i++) {
    std::cin >> d[i] >> p[i];
  }
  p[0] = p1, d[n + 1] = d1;

  double ans = 1e18;
  std::function<void(int, double, double)> dfs = 
  [&](int idx, double rst, double cur) {
    if (idx == n + 1) {
      ans = std::min(ans, cur);
      return;
    }
    if (c * d2 < d[idx + 1] - d[idx]) {
      return;
    }
    for (int i = idx + 1; i <= n + 1; i++) {
      double nxt = d[i] - d[idx];
      if (c * d2 < nxt) {
        break;
      }
      dfs(i, c - nxt / d2, cur + (c - rst) * p[idx]);
      dfs(i, 0, cur + std::max(0., p[idx] * (nxt / d2 - rst)));
    }
  };

  dfs(0, 0, 0);

  if (ans == 1e18) {
    std::cout << "No Solution\n";
  } else {
    std::cout << ans << "\n";
  }

  return 0;
}