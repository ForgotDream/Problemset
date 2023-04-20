/**
 * @file    LOJ#10004 智力大冲浪.cpp
 * @author  ForgotDream
 * @brief   贪心
 * @date    2023-03-20
 */
#include <bits/stdc++.h>

using i64 = long long;
using f80 = long double;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int m, n;
  std::cin >> m >> n;

  std::vector<std::pair<int, int>> a(n + 1);
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i].second;
  }
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i].first;
    a[i].first *= -1;
  }

  std::sort(a.begin() + 1, a.end());

  std::vector<bool> vis(501, false);
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    bool flg = true;
    for (int j = a[i].second; j; j--) {
      if (!vis[j]) {
        flg = false;
        vis[j] = true;
        break;
      }
    }
    if (flg) {
      for (int j = n; j; j--) {
        if (!vis[j]) {
          vis[j] = true;
          break;
        }
      }
      ans -= a[i].first;
    }
  }

  std::cout << m - ans << "\n";

  return 0;
}