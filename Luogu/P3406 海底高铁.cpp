/**
 * @file    P3406 海底高铁.cpp
 * @author  ForgotDream
 * @brief   Prefix Sum + Difference
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

  std::vector<int> d(n);
  int pre;
  std::cin >> pre;
  pre--;
  for (int i = 1; i < m; i++) {
    int c;
    std::cin >> c;
    c--;
    if (c < pre) {
      d[c]++, d[pre]--;
    } else {
      d[pre]++, d[c]--;
    }
    pre = c;
  }

  i64 sum = d[0], ans = 0;
  for (int i = 0; i < n - 1; i++, sum += d[i]) {
    int a, b, c;
    std::cin >> a >> b >> c;
    ans += std::min(sum * b + c, sum * a);
  }

  std::cout << ans << "\n";

  return 0;
}