/**
 * @file    AT_dp_z Frog 3.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-06-20
 */
#include <bits/stdc++.h>

using i64 = long long;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  i64 c;
  std::cin >> n >> c;

  std::vector<i64> h(n + 1);
  for (int i = 1; i <= n; i++) { std::cin >> h[i]; }

  std::vector<i64> f(n + 1);
  auto X = [&](int i) { return 2 * h[i]; };
  auto Y = [&](int i) { return f[i] + h[i] * h[i]; };
  auto up = [&](int i, int j) { return Y(i) - Y(j); };
  auto down = [&](int i, int j) { return X(i) - X(j); };
  
  std::vector<int> dq(2 * n);
  int p1 = 1, p2 = 1;
  dq[p2] = 1;
  for (int i = 2; i <= n; i++) {
    while (p1 < p2 && up(dq[p1 + 1], dq[p1]) <= h[i] * down(dq[p1 + 1], dq[p1])) {
      p1++;
    }
    f[i] = f[dq[p1]] + (h[i] - h[dq[p1]]) * (h[i] - h[dq[p1]]) + c;
    while (p1 < p2 && 
           up(i, dq[p2]) * down(dq[p2], dq[p2 - 1]) <= up(dq[p2], dq[p2 - 1]) * down(i, dq[p2])) {
      p2--;
    }
    dq[++p2] = i;
  }
  std::cout << f[n] << "\n";

  return 0;
}
