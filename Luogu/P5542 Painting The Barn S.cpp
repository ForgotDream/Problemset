/**
 * @file    P5542 Painting The Barn S.cpp
 * @author  ForgotDream
 * @brief   2D Difference
 * @date    2023-05-04
 */
#include <bits/stdc++.h>

using i64 = long long;
using i64u = unsigned long long;
using f80 = long double;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  constexpr int N = 1001;

  int n, k;
  std::cin >> n >> k;

  std::vector d(N, std::vector<int>(N, 0));
  for (int i = 0; i < n; i++) {
    int x1, y1, x2, y2;
    std::cin >> x1 >> y1 >> x2 >> y2;
    d[x1][y1]++;
    d[x2][y2]++;
    d[x1][y2]--;
    d[x2][y1]--;
  }

  int ans = 0;
  std::vector sum(N, std::vector<int>(N, 0));
  for (int i = 0; i <= 1000; i++) {
    for (int j = 0; j <= 1000; j++) {
      sum[i][j] = d[i][j];
      if (i && j) {
        sum[i][j] += sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
      } else if (i) {
        sum[i][j] += sum[i - 1][j];
      } else if (j) {
        sum[i][j] += sum[i][j - 1];
      }
      if (sum[i][j] == k) {
        ans++;
      }
    }
  }

  std::cout << ans << "\n";

  return 0;
}