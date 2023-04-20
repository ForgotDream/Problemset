/**
 * @file    LOJ#10002 喷水装置.cpp
 * @author  ForgotDream
 * @brief   贪心
 * @date    2023-03-17
 */
#include <bits/stdc++.h>

using i64 = long long;
using f80 = long double;

struct Circle {
  long double l, r;

  bool operator< (const Circle &oth) const {
    return l < oth.l;
  }
};

void solve() {
  int n;
  f80 l, w;
  std::cin >> n >> l >> w;

  std::vector<Circle> a;
  for (int i = 1; i <= n; i++) {
    f80 x, rad;
    std::cin >> x >> rad;
    
    if (rad < w / 2) {
      continue;
    }

    Circle t;
    f80 dis = std::sqrt((rad * rad) - ((w / 2) * (w / 2)));
    t.l = x - dis;
    t.r = x + dis;

    a.push_back(t);
  }

  std::sort(a.begin(), a.end());
  
  int pivot = 0, ans = 0;
  f80 t = 0;

  while (t < l) {
    f80 s = t;
    for (; a[pivot].l <= s && pivot < a.size(); pivot++) {
      if (a[pivot].r > t) {
        t = a[pivot].r;
      }
    }

    if (s == t) {
      std::cout << -1 << "\n";
      return;
    }

    ans++;
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