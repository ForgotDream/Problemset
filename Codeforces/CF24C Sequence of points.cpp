/**
 * @file    CF24C Sequence of points.cpp
 * @author  ForgotDream
 * @brief   Ad Hoc
 * @date    2023-08-23
 */
#include <cmath>
#include <iostream>

using i64 = long long;

constexpr int N = 1e5 + 50;
int n;
i64 x, sx, sy, ax[N], ay[N];
void solve() {
  std::cin >> n >> x;
  x = x % (2 * n);
  std::cin >> sx >> sy;
  for (int i = 1; i <= n; i++) std::cin >> ax[i] >> ay[i];
  for (int i = 1; i <= x; i++) {
    int cur = i > n ? i - n : i;
    i64 dx = std::abs(sx - ax[cur]), dy = std::abs(sy - ay[cur]);
    sx += (sx < ax[cur] ? 2 : -2) * dx;
    sy += (sy < ay[cur] ? 2 : -2) * dy;
  }
  std::cout << sx << " " << sy << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve();
  return 0;
}