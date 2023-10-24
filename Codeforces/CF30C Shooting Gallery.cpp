/**
 * @file    CF30C Shooting Gallery.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-08-23
 */
#include <algorithm>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <numeric>

using i64 = long long;
using f80 = long double;

constexpr int N = 1050;
int n, x[N], y[N], t[N], a[N];
f80 p[N], f[N];
bool check(int i, int j) {
  f80 dis = std::hypot(x[i] - x[j], y[i] - y[j]);
  int time = t[i] - t[j];
  return dis <= time;
}
void solve() {
  std::cout << std::fixed << std::setprecision(10);
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> x[i] >> y[i] >> t[i] >> p[i];

  std::iota(a + 1, a + n + 1, 1);
  std::sort(a + 1, a + n + 1, [&](int lhs, int rhs) {
    return t[lhs] < t[rhs];
  });

  f80 ans = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j < n; j++) {
      if (check(a[i], a[j])) f[a[i]] = std::max(f[a[i]], f[a[j]]);
    }
    f[a[i]] += p[a[i]];
    ans = std::max(ans, f[a[i]]);
  }

  std::cout << ans << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve();
  return 0;
}