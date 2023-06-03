#include <bits/stdc++.h>

using i64 = long long;

constexpr int d[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int h, w;
  std::cin >> h >> w;

  std::vector<std::string> a(h);
  for (int i = 0; i < h; i++) {
    std::cin >> a[i];
  }

  auto valid = [&](int x, int y) {
    return x >= 0 && x < h && y >= 0 && y < w;
  };

  const std::string s = "snuke";
  auto find = [&](int x, int y, int p) {
    int cnt = 0;
    int sx = x, sy = y;
    while (cnt < 5 && valid(x, y) && s[cnt] == a[x][y]) {
      x += d[p][0], y += d[p][1];
      cnt++;
    }
    if (cnt == 5) {
      for (int i = 0; i < 5; i++) {
        std::cout << sx + 1 << " " << sy + 1 << "\n";
        sx += d[p][0], sy += d[p][1];
      }
      return true;
    } else {
      return false;
    }
  };

  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      if (a[i][j] != 's') {
        continue;
      }
      for (int k = 0; k < 8; k++) {
        if (find(i, j, k)) {
          break;
        }
      }
    }
  }

  return 0;
}