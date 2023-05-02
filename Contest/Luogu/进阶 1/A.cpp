#include <bits/stdc++.h>

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int x1, y1, x2, y2;
  std::cin >> x1 >> y1 >> x2 >> y2;

  int dx = std::abs(x2 - x1), dy = std::abs(y2 - y1), d = std::gcd(dx, dy);
  dx /= d, dy /= d;

  std::cout << x1 + dx << " " << y1 - dy << "\n";

  return 0;
}