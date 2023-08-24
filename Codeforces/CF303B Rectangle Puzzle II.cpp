/**
 * @file    CF303B Rectangle Puzzle II.cpp
 * @author  ForgotDream
 * @brief   Ad Hoc
 * @date    2023-08-21
 */
#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>
#include <tuple>

using i64 = long long;
using ti4 = std::tuple<int, int, int, int>;

int n, m, x, y, a, b;

ti4 calc(int x1, int y1, int x2, int y2) {
  if (x1 < 0) x2 += -x1, x1 = 0;
  if (x2 > n) x1 -= x2 - n, x2 = n;
  if (y1 < 0) y2 += -y1, y1 = 0;
  if (y2 > m) y1 -= y2 - m, y2 = m;
  return std::make_tuple(x1, y1, x2, y2);
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n >> m >> x >> y >> a >> b;
  int gcd = std::gcd(a, b), da = a / gcd, db = b / gcd;
  int t = std::min(n / da, m / db);
  int h = t * da, w = t * db;
  int hh = h / 2, hw = w / 2;

  int x1 = x - hh, y1 = y - hw, x2 = x + hh + (h & 1), y2 = y + hw + (w & 1);
  std::vector<ti4> a;
  
  a.emplace_back(calc(x1, y1, x2, y2));
  if (h & 1) a.emplace_back(calc(x1 - 1, y1, x2 - 1, y2));
  if (w & 1) a.emplace_back(calc(x1, y1 - 1, x2, y2 - 1));
  if ((h & 1) && (w & 1)) a.emplace_back(calc(x1 - 1, y1 - 1, x2 - 1, y2 - 1));

  auto ans = *std::min_element(a.begin(), a.end());
  x1 = std::get<0>(ans), y1 = std::get<1>(ans);
  x2 = std::get<2>(ans), y2 = std::get<3>(ans);
  std::cout << x1 << " " << y1 << " " << x2 << " " << y2 << "\n";

  return 0;
}