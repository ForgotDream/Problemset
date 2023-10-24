/**
 * @file    CF1841D Pairs Of Segments.cpp
 * @author  ForgotDream
 * @brief   Greedy + Brute Force
 * @date    2023-06-22
 */
#include <bits/stdc++.h>

using i64 = long long;
using seg = std::pair<int, int>;

void solve() {
  int n;
  std::cin >> n;
  std::vector<seg> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i].first >> a[i].second;
  }
  std::vector<seg> ints;
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      int l = std::max(a[i].first, a[j].first);
      int r = std::min(a[i].second, a[j].second);
      if (l <= r) {
        l = std::min(a[i].first, a[j].first);
        r = std::max(a[i].second, a[j].second);
        ints.emplace_back(l, r);
      }
    }
  }
  std::sort(ints.begin(), ints.end(), [&](seg lhs, seg rhs) {
    return lhs.second < rhs.second;
  });
  int ans = 0, pre = -1;
  for (auto i : ints) {
    if (i.first > pre) {
      ans++, pre = i.second;
    }
  }
  std::cout << n - 2 * ans << "\n";
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
