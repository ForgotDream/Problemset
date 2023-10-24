/**
 * @file    LOJ#10008 家庭作业.cpp
 * @author  ForgotDream
 * @brief   贪心
 * @date    2023-03-20
 */
#include <bits/stdc++.h>

using i64 = long long;
using f80 = long double;

struct Homework {
  int t, w;
  bool operator< (const Homework &oth) const {
    if (w == oth.w) {
      return t < oth.t;
    } else {
      return w > oth.w;
    }
  }
};

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  int max = 0;
  std::vector<Homework> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i].t >> a[i].w;
    max = std::max(max, a[i].t);
  }

  std::sort(a.begin(), a.end());

  std::vector<bool> vis(max + 1);
  int cur = 1, ans = 0;
  for (int i = 0; i < n; i++) {
    bool flg = true;
    
    for (int j = a[i].t; j >= cur; j--) {
      if (!vis[j]) {
        flg = false;
        vis[j] = true;
        ans += a[i].w;
        break;
      }
    }

    if (flg) {
      cur = a[i].t;
    }
  }

  std::cout << ans << "\n";

  return 0;
}