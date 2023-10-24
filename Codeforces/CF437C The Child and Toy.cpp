/**
 * @file    CF437C The Child and Toy.cpp
 * @author  ForgotDream
 * @brief   Ad Hoc
 * @date    2023-08-09
 */
#include <bits/stdc++.h>
using i64 = long long;
constexpr int N = 1050;
int n, m, a[N], ans;
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  for (int i = 1, u, v; i <= m; i++) {
    std::cin >> u >> v;
    ans += std::min(a[u], a[v]);
  }
  std::cout << ans << "\n";
;  return 0;
}