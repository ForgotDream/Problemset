/**
 * @file    P2900 Land Acquisition G.cpp
 * @author  ForgotDream
 * @brief   Slope + DP
 * @date    2023-06-26
 */
#include <bits/stdc++.h>

using i64 = long long;
using mat = std::pair<i64, i64>;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  std::vector<mat> a(n + 2);
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i].first >> a[i].second;
  }

  std::sort(a.begin() + 1, a.end() - 1, std::greater<mat>());
  int p = 0;
  for (int i = 1; i <= n; i++) {
    if (a[i].second > a[p].second) {
      a[++p] = a[i];
    }
  }
  n = p;

  std::vector<i64> f(n + 1);
  auto X = [&](int i) {
    return -a[i + 1].first;
  };
  auto Y = [&](int i) {
    return f[i];
  };
  auto up = [&](int i, int j) {
    return Y(i) - Y(j);
  };
  auto down = [&](int i, int j) {
    return X(i) - X(j);
  };

  std::vector<int> q(n + 1);
  int p1 = 1, p2 = 1;
  for (int i = 1; i <= n; i++) {
    while (p1 < p2 &&
        up(q[p1], q[p1 + 1]) >= a[i].second * down(q[p1], q[p1 + 1])) {
      p1++;
    }
    f[i] = f[q[p1]] + 1ll * a[q[p1] + 1].first * a[i].second;
    while (p1 < p2 &&
        up(q[p2 - 1], q[p2]) * down(q[p2], i) >=
        up(q[p2], i) * down(q[p2 - 1], q[p2])) {
      p2--;
    }
    q[++p2] = i;
    // std::cerr << p1 << " " << p2 << "\n";
  }

  // for (int i = 1; i <= n; i++) {
  //   std::cerr << f[i] << " \n"[i == n];
  // }
  std::cout << f[n] << "\n";

  return 0;
}
