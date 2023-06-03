/**
 * @file    CF1830B The BOSS Can Count Pairs.cpp
 * @author  ForgotDream
 * @brief   Sqrt Data Structure
 * @date    2023-05-30
 */
#include <bits/stdc++.h>

using i64 = long long;

void solve() {
  int n;
  std::cin >> n;

  std::vector<std::pair<int, int>> c(n);
  for (int i = 0; i < n; i++) {
    std::cin >> c[i].first;
  }
  for (int i = 0; i < n; i++) {
    std::cin >> c[i].second;
  }

  std::sort(c.begin(), c.end());

  std::vector<int> cnt(n + 1);
  i64 ans = 0;
  for (int i = 1; i * i <= 2 * n; i++) {
    cnt.assign(n + 1, 0);
    for (auto [a, b] : c) {
      int p = a * i - b;
      if (1 <= p && p <= n) {
        ans += cnt[p];
      }
      if (a == i) {
        cnt[b]++;
      }
    }
  }

  std::cout << ans << "\n";
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