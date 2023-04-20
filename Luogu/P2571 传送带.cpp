/**
 * @file    P2571 传送带.cpp
 * @author  ForgotDream
 * @brief   三分
 * @date    2023-03-13
 */
#include <bits/stdc++.h>

using i64 = long long;
using f80 = long double;

struct Point {
  f80 x, y;

  Point() : x(0), y(0) {}
  Point(f80 x, f80 y) : x(x), y(y) {}
};

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Point a, b, c, d;
  f80 p, q, r;
  std::cin >> a.x >> a.y >> b.x >> b.y
           >> c.x >> c.y >> d.x >> d.y
           >> p >> q >> r;

  f80 dx, dy;
  std::vector<Point> m, n;

  dx = (b.x - a.x) / 8000;
  dy = (b.y - a.y) / 8000;
  for (int i = 0; i <= 8000; i++) {
    m.emplace_back(a.x + dx * i, a.y + dy * i);
  }

  dx = (d.x - c.x) / 8000;
  dy = (d.y - c.y) / 8000;
  for (int i = 0; i <= 8000; i++) {
    n.emplace_back(c.x + dx * i, c.y + dy * i);
  }

  auto dis = [](Point u, Point v) {
    return std::sqrt((u.x - v.x) * (u.x - v.x) + (u.y - v.y) * (u.y - v.y));
  };

  f80 ans = 1e16;
  for (auto i : m) {
    for (auto j : n) {
      ans = std::min(ans, dis(i, a) / p + dis(i, j) / r + dis(j, d) / q);
    }
  }

  std::cout << std::fixed << std::setprecision(2) << ans << "\n";

  return 0;
}