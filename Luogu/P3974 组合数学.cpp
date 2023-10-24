/**
 * @file    P3974 组合数学.cpp
 * @author  ForgotDream
 * @brief   Dilworth 定理 + DP
 * @date    2023-03-03
 */
#include <bits/stdc++.h>

using i64 = long long;

void solve() {
  int n, m;
  std::cin >> n >> m;
  std::vector<std::vector<i64>> a(n + 2, std::vector<i64>(m + 2, 0));
  auto f = a;

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      std::cin >> a[i][j];
    }
  }

  for (int i = 1; i <= n; i++) {
    for (int j = m; j >= 1; j--) {
      f[i][j] = f[i - 1][j + 1] + a[i][j];
      f[i][j] = std::max(f[i][j], std::max(f[i - 1][j], f[i][j + 1]));
    }
  }

  std::cout << f[n][1] << "\n";
  return;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  std::cin >> t;
  
  while (t--) {
    solve();
  }

  return 0;
}