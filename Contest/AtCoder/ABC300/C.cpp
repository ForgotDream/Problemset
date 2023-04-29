#include <bits/stdc++.h>

using i64 = long long;

constexpr int d[][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int h, w;
  std::cin >> h >> w;

  std::vector<std::string> c(h);
  for (int i = 0; i < h; i++) {
    std::cin >> c[i];
  }

  auto legal = [&](int x, int y) -> bool {
    return x >= 0 && y >= 0 && x < h && y < w && c[x][y] == '#';
  };

  std::vector<int> ans(std::min(h, w) + 1);
  auto solve = [&](int x, int y) -> void {
    int delta = 1;
    
    auto check = [&](int delta) -> bool {
      for (int i = 0; i < 4; i++) {
        if (!legal(x + delta * d[i][0], y + delta * d[i][1])) {
          return false;
        }
      }
      return true;
    };

    while (check(delta)) {
      // ans[delta]++;
      delta++;
    }

    if (delta != 1) {
      ans[delta - 1]++;
    }

    return;
  };

  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      // std::cerr << i << " " << j << "\n";
      if (c[i][j] == '#') {
        // std::cerr << i << " " << j << "\n";
        solve(i, j);
      }
    }
  }

  // std::cerr << "OK\n";

  for (int i = 1; i <= std::min(h, w); i++) {
    std::cout << ans[i] << " \n"[i == std::min(h, w)];
  }

  return 0;
}