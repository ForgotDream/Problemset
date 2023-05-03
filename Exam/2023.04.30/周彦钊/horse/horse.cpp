#include <bits/stdc++.h>

using i64 = long long;

namespace Helper {
void useFileIO() {
  freopen("horse.in", "r", stdin);
  freopen("horse.out", "w", stdout);
  return;
}
};

constexpr int dis[][6] = {
  {0, 3, 2, 3, 2, 3},
  {3, 2, 1, 2, 3, 4},
  {2, 1, 4, 3, 2, 3},
  {3, 2, 3, 2, 3, 4},
  {2, 3, 2, 3, 4, 3},
  {3, 4, 3, 4, 3, 4}
};

int main() {
  Helper::useFileIO();

  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int xp, yp, xs, ys;
  std::cin >> xp >> yp >> xs >> ys;

  int dx = std::abs(xp - xs), dy = std::abs(yp - ys);
  int ans = 0;

  while (dx > 5 || dy > 5) {
    if (dx > dy) {
      std::swap(dx, dy);
    }
    dx -= 1, dy -= 2;
    dx = std::abs(dx), dy = std::abs(dy);
    ans++;
  }

  std::cout << ans + dis[dx][dy] << "\n";

  return 0;
}