/**
 * @file    P6510 奶牛排队.cpp
 * @author  ForgotDream
 * @brief   Segment Tree + Divide and Conquer
 * @date    2023-05-04
 */
#include <bits/stdc++.h>

using i64 = long long;
using i64u = unsigned long long;
using f80 = long double;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  
  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  std::vector<std::pair<int, int>> min((n + 1) << 2), max((n + 1) << 2);

  std::function<void(int, int, int)> build = [&](int l, int r, int u) {
    if (l == r) {
      min[u] = max[u] = std::make_pair(a[l - 1], l);
      return;
    }
    int mid = (l + r) >> 1, lc = u << 1, rc = u << 1 | 1;
    build (l, mid, lc), build(mid + 1, r, rc);
    max[u] = max[rc].first >= max[lc].first ? max[rc] : max[lc];
    min[u] = min[rc].first < min[lc].first ? min[rc] : min[lc];
    return;
  };

  build(1, n, 1);

  std::function<std::pair<int, int>(int, int, int, int, int)> queryMax = 
  [&](int l, int r, int s, int t, int u) -> std::pair<int, int> {
    if (l <= s && t <= r) {
      return max[u];
    }
    std::pair<int, int> res = std::make_pair(0, t);
    int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
    if (l <= mid) {
      res = queryMax(l, r, s, mid, lc);
    }
    if (r > mid) {
      auto p = queryMax(l, r, mid + 1, t, rc);
      res = res.first > p.first ? res : p;
    }
    return res;
  };

  std::function<std::pair<int, int>(int, int, int, int, int)> queryMin = 
  [&](int l, int r, int s, int t, int u) -> std::pair<int, int> {
    if (l <= s && t <= r) {
      return min[u];
    }
    std::pair<int, int> res = std::make_pair(INT_MAX, s);
    int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
    if (l <= mid) {
      res = queryMin(l, r, s, mid, lc);
    }
    if (r > mid) {
      auto p = queryMin(l, r, mid + 1, t, rc);
      res = res.first <= p.first ? res : p;
    }
    return res;
  };

  std::function<int(int, int)> solve = [&](int l, int r) -> int {
    if (l >= r) {
      return 0;
    }
    int s = queryMin(l + 1, r + 1, 1, n, 1).second - 1;
    int t = queryMax(l + 1, r + 1, 1, n, 1).second - 1;
    if (s < t) {
      return std::max({
        solve(l, s - 1), 
        solve(t + 1, r), 
        t - s + 1
      });
    } else if (s > t) {
      return std::max({
        solve(l, t), 
        solve(t + 1, s - 1), 
        solve(s, r)
      });
    } else {
      return 0;
    }
  };

  std::cout << solve(0, n - 1) << "\n";

  return 0;
}