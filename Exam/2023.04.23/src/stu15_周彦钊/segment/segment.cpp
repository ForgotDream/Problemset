#include <bits/stdc++.h>

using i64 = long long;
using f80 = long double;

namespace myFile {
void useFileIO() {
  freopen("segment.in", "r", stdin);
  freopen("segment.out", "w", stdout);
  return;
}
}

struct Point {
  f80 x, y;
  Point() {}
  Point(f80 x, f80 y) : x(x), y(y) {}
  
  Point operator= (const Point &rhs) {
    x = rhs.x, y = rhs.y;
    return *this;
  }
};

bool operator< (const Point &lhs, const Point &rhs) {
  if (lhs.x == rhs.x) {
    return lhs.y < rhs.y;
  } else {
    return lhs.x < rhs.x;
  }
}

int main() {
  myFile::useFileIO();
  
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout << std::fixed << std::setprecision(4);
  
  static const f80 EPS = 1e-8;
  
  std::vector<Point> points(4);
  for (int i = 0; i < 4; i++) {
    std::cin >> points[i].x >> points[i].y;
  }
  
  std::sort(points.begin(), points.begin() + 2);
  std::sort(points.begin() + 2, points.end());
  
  auto getMinDis = [&](const Point &u) -> f80 {
    Point l(points[2].x, points[2].y), r(points[3].x, points[3].y);
    if (l.x == r.x && l.y == r.y) {
      return std::hypot(l.x - u.x, l.y - u.y);
    }
    f80 res = LONG_LONG_MAX;
    int d;
    if (l.y <= r.y) {
      d = 1;
    } else {
      d = -1;
    }
    while (std::hypot(l.x - r.x, l.y - r.y) > EPS) {
      Point lmid(l.x + std::fabs(r.x - l.x) / 3, l.y + d * std::fabs(r.y - l.y) / 3);
      Point rmid(r.x - std::fabs(r.x - l.x) / 3, r.y - d * std::fabs(r.y - l.y) / 3);
      f80 d1 = std::hypot(lmid.x - u.x, lmid.y - u.y);
      f80 d2 = std::hypot(rmid.x - u.x, rmid.y - u.y);
      if (d1 > d2 + EPS) {
        l = lmid;
        res = std::min(res, d2);
      } else {
        r = rmid;
        res = std::min(res, d1);
      }
    }
    return res;
  };
  
  Point l(points[0].x, points[0].y), r(points[1].x, points[1].y);
  int d;
  if (l.y <= r.y) {
    d = 1;
  } else {
    d = -1;
  }
  f80 res = LONG_LONG_MAX;
  if (l.x == r.x && l.y == r.y) {
    std::cout << getMinDis(l) << "\n";
    return 0;
  }
  while (std::hypot(l.x - r.x, l.y - r.y) > EPS) {
    Point lmid(l.x + std::fabs(r.x - l.x) / 3, l.y + d * std::fabs(r.y - l.y) / 3);
    Point rmid(r.x - std::fabs(r.x - l.x) / 3, r.y - d * std::fabs(r.y - l.y) / 3);
    f80 d1 = getMinDis(lmid), d2 = getMinDis(rmid);
    if (d1 > d2 + EPS) {
      l = lmid;
      res = std::min(res, d2);
    } else {
      r = rmid;
      res = std::min(res, d1);
    }
  }
  
  std::cout << res << "\n";
  
  return 0;
}
