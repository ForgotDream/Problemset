/**
 * @file    CF297B Fish Weight.cpp
 * @author  ForgotDream
 * @brief   Ad Hoc
 * @date    2023-08-20
 */
#include <algorithm>
#include <iostream>

using i64 = long long;

constexpr int N = 1e5 + 50;
int n, m, k;
int a[N], b[N];

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n >> m >> k;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  for (int i = 1; i <= m; i++) std::cin >> b[i];

  if (n > m) {
    std::cout << "YES\n";
    return 0;
  }

  std::sort(a + 1, a + n + 1);
  std::sort(b + 1, b + m + 1);
  for (int i = 1; i <= n; i++) {
    if (a[i] > b[m - n + i]) {
      std::cout << "YES\n";
      return 0;
    }
  }

  std::cout << "NO\n";

  return 0;
}