/**
 * @file    P1209 [USACO1.3] 修理牛棚 Barn Repair.cpp
 * @author  ForgotDream
 * @brief   Greedy
 * @date    2023-08-07
 */
#include <bits/stdc++.h>
using i64 = long long;
constexpr int N = 250;
int m, s, c, a[N], ans;
int d[N], cnt;
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> m >> s >> c;
  for (int i = 1; i <= c; i++) std::cin >> a[i];
  if (m >= c) return std::cout << c << "\n", 0;
  std::sort(a + 1, a + c + 1);
  ans = a[c] - a[1] + 1;
  for (int i = 2; i <= c; i++) d[++cnt] = a[i] - a[i - 1] - 1;
  std::sort(d + 1, d + cnt + 1, std::greater<int>());
  for (int i = 1; i <= m - 1; i++) ans -= d[i];
  std::cout << ans << "\n";
  return 0;
}