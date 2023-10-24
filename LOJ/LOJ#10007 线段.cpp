/**
 * @file    LOJ#10007 线段.cpp
 * @author  ForgotDream
 * @brief   贪心
 * @date    2023-03-20
 */
#include <bits/stdc++.h>

using i64 = long long;
using f80 = long double;

struct Segment {
  int l, r;
  bool operator< (const Segment &oth) const {
    if (r == oth.r) {
      return l > oth.l;
    } else {
      return r < oth.r;
    }
  }
};

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  std::vector<Segment> a(n + 1);
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i].l >> a[i].r;
  }

  std::sort(a.begin() + 1, a.end());

  int cur = 0, ans = 0;
  for (int i = 1; i <= n; i++) {
    if (a[i].l >= a[cur].r) {
      ans++;
      cur = i;
    }
  }

  std::cout << ans << "\n";

  return 0;
}