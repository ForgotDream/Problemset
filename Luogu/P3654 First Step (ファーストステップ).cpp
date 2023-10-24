/**
 * @file    P3654 First Step (ファーストステップ).cpp
 * @author  ForgotDream
 * @brief   枚举
 * @date    2023-03-20
 */
#include <bits/stdc++.h>

using i64 = long long;
using f80 = long double;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m, k;
  std::cin >> n >> m >> k;

  std::vector<std::vector<bool>> a(n, std::vector<bool>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      char c;
      std::cin >> c;
      a[i][j] = (c == '.');
    }
  }

  i64 ans = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (!a[i][j]) {
        continue;
      }
      // expand part
      for (int dy = j; dy < m && a[i][dy]; dy++) {
        if (dy - j + 1 >= k) {
          ans++;
          break;
        }
      }
      for (int dx = i; dx < n && a[dx][j]; dx++) {
        if (dx - i + 1 >= k) {
          ans++;
          break;
        }
      }
      if (k == 1) {
        ans--;
      }
    }
  }

  std::cout << ans << "\n";

  return 0;
}