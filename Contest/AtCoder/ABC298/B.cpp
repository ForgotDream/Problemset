#include <bits/stdc++.h>

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int n;
  std::cin >> n;

  std::vector<std::vector<int>> a(n, std::vector<int>(n));
  auto b = a;
  bool ans = true;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      std::cin >> a[i][j];
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      std::cin >> b[i][j];
      if (a[i][j] == 1) {
        if (b[i][j] == 1) {
          continue;
        } else {
          ans = false;
        }
      }
    }
  }

  if (ans) {
    std::cout << "Yes" << "\n";
    return 0;
  }

  for (int i = 0; i < 4; i++) {
    bool cur = true;
    auto c = a;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        c[i][j] = a[n - j - 1][i];
        if (c[i][j] == 1) {
          if (b[i][j] == 1) {
            continue;
          } else {
            cur = false;
          }
        }
      }
    }
    if (cur) {
      std::cout << "Yes" << "\n";
      return 0;
    }
    a = c;
  }

  std::cout << "No" << "\n";

  return 0;
}