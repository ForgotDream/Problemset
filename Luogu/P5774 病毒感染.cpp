/**
 * @file    P5774 病毒感染.cpp
 * @author  ForgotDream
 * @brief   Interval DP
 * @date    2023-06-07
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr i64 inf = 1e12;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  std::vector<i64> a(n);
  for (int i = 0; i < n; i++) { std::cin >> a[i]; }
  
  std::vector<i64> s(n);
  std::partial_sum(a.begin(), a.end(), s.begin());

  auto sum = [&](int l, int r) { return s[r] - (l ? s[l - 1] : 0); };

  std::vector f(n, std::vector<i64>(n));
  for (int len = 2; len <= n; len++) {
    for (int l = 0; l + len - 1 < n; l++) {
      int r = l + len - 1;
      i64 curSum = sum(l + 1, r);
      f[l][r] = f[l + 1][r] + curSum + std::min(3 * (r - l) * a[l], curSum);
    }
  }

  std::vector<i64> g(n, inf);
  for (int r = 0; r < n; r++) {
    g[r] = f[0][r] + sum(r + 1, n - 1) * (4 * r + 2);
    for (int l = 0; l < r; l++) {
      int len = r - (l + 1);
      g[r] = std::min(
        g[r], 
        f[l + 1][r] + g[l] + sum(r + 1, n - 1) * (4 * len + 2));
    }
  }

  std::cout << g[n - 1] << "\n";

  return 0;
}