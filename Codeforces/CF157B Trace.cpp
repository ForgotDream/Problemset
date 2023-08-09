/**
 * @file    CF157B Trace.cpp
 * @author  ForgotDream
 * @brief   Ad Hoc
 * @date    2023-08-07
 */
#include <bits/stdc++.h>
using i64 = long long;
using f80 = long double;
constexpr int N = 105;
int n, a[N];
f80 pi = std::acos(-1), ans = 0;
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout << std::fixed << std::setprecision(10);
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  std::sort(a + 1, a + n + 1, std::greater<int>());
  for (int i = 1; i <= n; i++) ans += (i & 1 ? 1 : -1) * pi * a[i] * a[i];
  std::cout << ans << "\n";
  return 0;
}