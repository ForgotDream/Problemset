#include <bits/stdc++.h>

using i64 = long long;
using f80 = long double;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int r, c;
  std::cin >> r >> c;

  std::vector<std::string> a(r);
  for (int i = 0; i < r; i++) {
    std::cin >> a[i];
  }

  auto dis = [](f80 x1, f80 y1, f80 x2, f80 y2) -> f80 {
    return std::abs(x1 - x2) + std::abs(y1 - y2);
  };

  auto ans = a;
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      if (isdigit(a[i][j])) {
        ans[i][j] = '.';
        for (int n = 0; n < r; n++) {
          for (int m = 0; m < c; m++) {
            if (dis(i, j, n, m) <= a[i][j] - '0' && a[n][m] == '#') {
              ans[n][m] = '.';
            }
          }
        }
      }
    }
  }

  for (int i = 0; i < r; i++) {
    std::cout << ans[i] << '\n';
  }

  return 0;
}