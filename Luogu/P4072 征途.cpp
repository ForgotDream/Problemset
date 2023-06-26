/**
 * @file    P4072 征途.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-06-26
 */
#include <bits/stdc++.h>

using i64 = long long;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  std::vector<i64> a(n + 1);
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i];
  }

  std::vector<i64> sum(n + 1), g(n + 1);
  for (int i = 1; i <= n; i++) {
    sum[i] = sum[i - 1] + a[i];
    g[i] = sum[i] * sum[i];
  }

  std::vector<i64> f(n + 1);
  auto X = [&](int i) {
    return 2 * sum[i];
  };
  auto Y = [&](int i) {
    return g[i] + sum[i] * sum[i];
  };
  auto up = [&](int i, int j) {
    return Y(i) - Y(j);
  };
  auto down = [&](int i, int j) {
    return X(i) - X(j);
  };

  std::vector<int> q(n + 1);
  for (int i = 1; i < m; i++) {
    int p1 = 1, p2 = 1;
    q[1] = i;
    for (int j = i + 1; j <= n; j++) {
      while (p1 < p2 && 
          up(q[p1], q[p1 + 1]) >= sum[j] * down(q[p1], q[p1 + 1])) {
        p1++;
      }
      f[j] = g[q[p1]] + (sum[j] - sum[q[p1]]) * (sum[j] - sum[q[p1]]);
      while (p1 < p2 && 
          up(q[p2 - 1], q[p2]) * down(q[p2], j) >=
          down(q[p2 - 1], q[p2]) * up(q[p2], j)) {
        p2--;
      }
      q[++p2] = j;
    }
    g = f;
  }

  std::cout << m * f[n] - sum[n] * sum[n] << "\n";

  return 0;
}
