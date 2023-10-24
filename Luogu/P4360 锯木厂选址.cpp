/**
 * @file    P4360 锯木厂选址.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-06-29
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr i64 inf = 1e15;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  n++;

  std::vector<i64> w(n + 1), d(n + 1);
  for (int i = 1; i < n; i++) {
    std::cin >> w[i] >> d[i + 1];
  }

  std::vector<i64> sum(n + 1), cost(n + 1);
  std::partial_sum(d.begin(), d.end(), d.begin());
  for (int i = 1; i <= n; i++) {
    sum[i] = sum[i - 1] + w[i];
    cost[i] = cost[i - 1] + w[i] * d[i];
  }

  auto X = [&](int i) {
    return sum[i];
  };
  auto Y = [&](int i) {
    return d[i] * sum[i];
  };
  auto slope = [&](int i, int j) {
    return 1. * (Y(i) - Y(j)) / (X(i) - X(j));
  };

  std::vector<int> q(n + 1);
  int p1 = 1, p2 = 1;
  i64 ans = inf;
  for (int i = 1; i < n; i++) {
    while (p1 < p2 && slope(q[p1], q[p1 + 1]) < d[i]) {
      p1++;
    }
    int j = q[p1];
    ans = std::min(
        ans, d[j] * sum[j] + cost[0] +
          d[i] * (sum[i] - sum[j]) +
          d[n] * (sum[n] - sum[i]) - cost[n]);
    while (p1 < p2 && slope(q[p2 - 1], q[p2]) > slope(q[p2], i)) {
      p2--;
    }
    q[++p2] = i;
  }
  std::cout << ans << "\n";

  return 0;
}