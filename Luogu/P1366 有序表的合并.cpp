/**
 * @file    P1366 有序表的合并.cpp
 * @author  ForgotDream
 * @brief   Two Pointers
 * @date    2023-05-03
 */
#include <bits/stdc++.h>

using i64 = long long;
using i64u = unsigned long long;
using f80 = long double;

void solve() {
  int n, m;
  std::cin >> n >> m;

  std::vector<i64u> a(n + 1), b(m + 1);
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i];
  }
  for (int i = 1; i <= m; i++) {
    std::cin >> b[i];
  }

  int ans = 0, pivot = 1;
  for (int i = 1; i <= n; i++) {
    int cnt = 0;
    while (pivot <= m && b[pivot] <= a[i]) {
      if (b[pivot] == a[i]) {
        cnt++;
      }
      pivot++;
    }
    ans ^= cnt;
  }

  std::cout << ans << "\n";

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