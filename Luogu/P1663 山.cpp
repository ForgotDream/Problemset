/**
 * @file    P1663 山.cpp
 * @author  ForgotDream
 * @brief   二分
 * @date    2023-03-13
 */
#include <bits/stdc++.h>

using i64 = long long;
using f80 = long double;

struct Point {
  f80 x, y;
  Point() {}
};

struct Line {
  f80 k, b;
  Line() {}
};

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  static const f80 EPS = 1e-10;

  int n;
  std::cin >> n;

  std::vector<Point> point(n);
  std::vector<Line> line(n);
  std::cin >> point[0].x >> point[0].y;
  for (int i = 1; i < n; i++) {
    std::cin >> point[i].x >> point[i].y;
    line[i].k = (point[i].y - point[i - 1].y) / (point[i].x - point[i - 1].x);
    line[i].b = point[i].y - line[i].k * point[i].x;
  }

  auto check = [&](f80 mid) {
    f80 maxx = -1e18, minn = 1e18;
    for (int i = 1; i < n; i++) {
      if (line[i].k < 0) {
        maxx = std::max(maxx, (mid - line[i].b) / line[i].k);
      } else if (line[i].k > 0) {
        minn = std::min(minn, (mid - line[i].b) / line[i].k);
      } else if (mid < line[i].b) {
        return false;
      }
    }
    return maxx <= minn;
  };

  f80 l = 0, r = 1e18;
  while (r - l >= EPS) {
    f80 mid = (l + r) / 2;
    if (check(mid)) {
      r = mid;
    } else {
      l = mid;
    }
  }

  std::cout << std::fixed << std::setprecision(2) << r << "\n";

  return 0;
}