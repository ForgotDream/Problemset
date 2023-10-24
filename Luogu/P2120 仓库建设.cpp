/**
 * @file    P2120 仓库建设.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-06-29
 */
#include <bits/stdc++.h>

using i64 = long long;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  std::vector<i64> x(n + 1), p(n + 1), c(n + 1);
  std::vector<i64> sum(n + 1), cost(n + 1);
  for (int i = 1; i <= n; i++) {
    std::cin >> x[i] >> p[i] >> c[i];
    sum[i] = p[i] + sum[i - 1];
    cost[i] = p[i] * x[i] + cost[i - 1];
  }

  std::vector<i64> f(n + 1);
  auto X = [&](int i) {
    return sum[i];
  };
  auto Y = [&](int i) {
    return f[i] + cost[i];
  };
  auto up = [&](int i, int j) {
    return X(i) - X(j);
  };
  auto down = [&](int i, int j) {
    return Y(i) - Y(j);
  };

  std::vector<int> q(n + 1);
  int p1 = 1, p2 = 1;
  for (int i = 1; i <= n; i++) {
    while (p1 < p2 && 
        Y(q[p1 + 1]) - Y(q[p1]) < x[i] * (X(q[p1 + 1]) - X(q[p1]))) {
      p1++;
    }
    int j = q[p1];
    f[i] = f[j] + x[i] * (sum[i] - sum[j]) - (cost[i] - cost[j]) + c[i];
    while (p1 < p2 &&
        up(q[p2], q[p2 - 1]) * down(i, q[p2]) < 
        down(q[p2], q[p2 - 1]) * up(i, q[p2])) {
      p2--;
    }
    q[++p2] = i;
  }

  int pivot = n;
  while (pivot >= 1 && p[pivot] == 0) {
    pivot--;
  }
  std::cout << *std::min_element(f.begin() + pivot, f.end()) << "\n";

  return 0;
}
