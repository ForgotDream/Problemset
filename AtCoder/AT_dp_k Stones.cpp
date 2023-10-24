/**
 * @file    AT_dp_k Stone.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-06-19
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int d = 1e5;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, k;
  std::cin >> n >> k;

  std::vector<int> a(n);
  std::bitset<d + 1> valid;
  for (int i = 0; i < n; i++) { std::cin >> a[i], valid[a[i]] = true; }

  std::vector f(k + 1, std::vector<int>(2, -1));
  std::function<int(int, int)> dfs = [&](int rst, int u) {
    if (rst < a[0]) { return f[rst][u] = 0; }
    if (f[rst][u] != -1) { return f[rst][u]; }
    int res = 0;
    for (int i = 0; i < n && a[i] <= rst; i++) {
      res |= !(dfs(rst - a[i], u ^ 1));
    }
    return f[rst][u] = res;
  };

  if (dfs(k, 0)) {
    std::cout << "First\n";
  } else {
    std::cout << "Second\n";
  }

  return 0;
}