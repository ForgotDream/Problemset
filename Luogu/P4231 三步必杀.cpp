/**
 * @file    P4231 三步必杀.cpp
 * @author  ForgotDream
 * @brief   2D Difference
 * @date    2023-05-04
 */
#include <bits/stdc++.h>

using i64 = long long;
using i64u = unsigned long long;
using f80 = long double;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  std::vector<i64> d2(n);
  for (int i = 0; i < m; i++) {
    int l, r;
    i64 s, e;
    std::cin >> l >> r >> s >> e;
    l--, r--;
    if (l == r) {
      d2[l] += s;
      if (r != n - 1) {
        d2[r + 1] -= 2 * s;
      }
    } else {
      i64 delta  = (e - s) / (r - l);
      d2[l] += s;
      if (l != n - 1) {
        d2[l + 1] -= s - delta;
      }
      if (r != n - 1) {
        d2[r + 1] -= e + delta;
      }
      if (r < n - 2) {
        d2[r + 2] += e;
      }
    }
  }

  std::vector<i64> d(n);
  for (int i = 0; i < n; i++) {
    d[i] = d2[i] + (i ? d[i - 1] : 0);
    // std::cerr << d2[i] << " " << d[i] << "\n";
  }

  i64 cur = 0, sum = 0, max = LONG_LONG_MIN;
  for (int i = 0; i < n; i++) {
    cur += d[i];
    sum ^= cur;
    max = std::max(max, cur);
  }

  std::cout << sum << " " << max << "\n";

  return 0;
}