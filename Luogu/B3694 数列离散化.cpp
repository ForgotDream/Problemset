/**
 * @file    B3694 数列离散化.cpp
 * @author  ForgotDream
 * @brief   Discretization
 * @date    2023-05-03
 */
#include <bits/stdc++.h>

using i64 = long long;
using i64u = unsigned long long;
using f80 = long double;

void solve() {
  int n;
  std::cin >> n;

  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  auto b = a;
  std::sort(b.begin(), b.end());
  b.erase(std::unique(b.begin(), b.end()), b.end());

  for (int i = 0; i < n; i++) {
    int u = std::lower_bound(b.begin(), b.end(), a[i]) - b.begin();
    std::cout << u + 1 << " \n"[i == n - 1];
  }

  return;
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  std::cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}