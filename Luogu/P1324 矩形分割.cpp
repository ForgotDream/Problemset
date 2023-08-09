/**
 * @file    P1324 矩形分割.cpp
 * @author  ForgotDream
 * @brief   Greedy
 * @date    2023-08-08
 */
#include <bits/stdc++.h>
using i64 = long long;
constexpr int N = 2050;
int n, m, a[N], b[N];
i64 ans = 0;
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n >> m;
  for (int i = 1; i < n; i++) std::cin >> a[i];
  for (int i = 1; i < m; i++) std::cin >> b[i];
  std::sort(a + 1, a + n, std::greater<int>());
  std::sort(b + 1, b + m, std::greater<int>());
  int pa = 1, pb = 1;
  for (int i = 1; i <= n + m - 2; i++) {
    if (a[pa] > b[pb]) ans += 1ll * pb * a[pa++];
    else ans += 1ll * pa * b[pb++];
  }
  std::cout << ans << "\n";
  return 0;
}