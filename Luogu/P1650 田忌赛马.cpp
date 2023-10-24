/**
 * @file    P1650 田忌赛马.cpp
 * @author  ForgotDream
 * @brief   Greedy
 * @date    2023-08-08
 */
#include <bits/stdc++.h>
using i64 = long long;
constexpr int N = 2050;
int n, a[N], b[N], ans;
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  for (int i = 1; i <= n; i++) std::cin >> b[i];
  std::sort(a + 1, a + n + 1);
  std::sort(b + 1, b + n + 1);
  int ha = 1, hb = 1, ta = n, tb = n;
  for (int i = 1; i <= n; i++) {
    if (a[ta] > b[tb]) ans += 200, ta--, tb--;
    else if (a[ha] > b[hb]) ans += 200, ha++, hb++;
    else ans -= (a[ha] == b[tb] ? 0 : 200), ha++, tb--;
  }
  std::cout << ans << "\n";
  return 0;
}