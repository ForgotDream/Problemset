#include <bits/stdc++.h>

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  std::vector<std::string> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  auto check = [&](int x, int y) {
    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        int dx = x + i, dy = y + j;
        if (i < 3 && j < 3) {
          if (a[dx][dy] == '.') {
            return false;
          }
        } else if ((i == 3 && j <= 3) || (j == 3 && i <= 3)) {
          if (a[dx][dy] == '#') {
            return false;
          }
        } else if ((i == 5 && j >= 5) || (j == 5 && i >= 5)) {
          if (a[dx][dy] == '#') {
            return false;
          }
        } else if (i >= 6 && j >= 6) {
          if (a[dx][dy] == '.') {
            return false;
          }
        }
      }
    }
    return true;
  };

  for (int i = 0; i < n - 8; i++) {
    for (int j = 0; j < m - 8; j++) {
      if (a[i][j] == '.') {
        continue;
      }
      if (check(i, j)) {
        std::cout << i + 1 << " " << j + 1 << "\n";
      }
    }
  }

  return 0;
}