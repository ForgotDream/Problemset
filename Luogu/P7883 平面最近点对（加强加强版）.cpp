/**
 * @file    P7883 平面最近点对（加强加强版）.cpp
 * @author  ForgotDream
 * @brief   Divide and Conquer
 * @date    2023-10-23
 */
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using i64 = long long;

constexpr int N = 4e5 + 50;
int n;
struct Point {
  i64 x, y;
} a[N];
inline i64 dis(const Point &i, const Point &j) {
  i64 x = (i.x - j.x) * (i.x - j.x);
  i64 y = (i.y - j.y) * (i.y - j.y);
  return x + y;
}
i64 solve(Point *l, Point *r) {
  i64 res = 1e18;
  if (r - l <= 1) return res;
  auto mid = l + (r - l) / 2;
  i64 midx = mid->x;
  res = std::min(solve(l, mid), solve(mid, r));
  std::inplace_merge(l, mid, r, [&](const Point &lhs, const Point &rhs) {
    return lhs.y < rhs.y;
  });
  std::vector<Point> tmp;
  for (auto i = l; i != r; i++) {
    if (abs(midx - i->x) <= sqrt(res)) tmp.push_back(*i);
  }
  for (auto i = tmp.begin(); i != tmp.end(); i++) {
    for (auto j = i + 1; j != tmp.end() && j->y - i->y <= sqrt(res); j++) {
      i64 cur = dis(*i, *j);
      res = std::min(res, cur);
    }
  }
  return res;
}
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i].x >> a[i].y;
  std::sort(a + 1, a + n + 1,
            [&](const Point &lhs, const Point &rhs) { return lhs.x < rhs.x; });
  std::cout << solve(a + 1, a + n + 1) << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
