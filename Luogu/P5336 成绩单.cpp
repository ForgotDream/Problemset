/**
 * @file    P5336 成绩单.cpp
 * @author  ForgotDream
 * @brief   Interval DP
 * @date    2023-06-07
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int inf = 1e9;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, a, b;
  std::cin >> n >> a >> b;

  std::vector<int> w(n);
  for (int i = 0; i < n; i++) { std::cin >> w[i]; }

  auto disc = w;
  std::sort(disc.begin(), disc.end());
  disc.erase(std::unique(disc.begin(), disc.end()), disc.end());

  int m = disc.size();
  for (int i = 0; i < n; i++) {
    w[i] = std::lower_bound(disc.begin(), disc.end(), w[i]) - disc.begin();
  }

  std::vector f(n, std::vector(n, std::vector(m, std::vector<int>(m, inf))));
  std::vector g(n, std::vector<int>(n, inf));
  for (int i = 0; i < n; i++) { f[i][i][w[i]][w[i]] = 0; }
  for (int len = 1; len <= n; len++) {
    for (int l = 0; l + len - 1 < n; l++) {
      int r = l + len - 1;
      for (int min = 0; min < m; min++) {
        for (int max = min; max < m; max++) {
          for (int k = l; k < r; k++) {
            f[l][r][min][max] = std::min(
              f[l][r][min][max], 
              f[l][k][min][max] + g[k + 1][r]
            );
          }
          if (r != n - 1) {
            int curMin = std::min(min, w[r + 1]);
            int curMax = std::max(max, w[r + 1]);
            f[l][r + 1][curMin][curMax] = std::min(
              f[l][r + 1][curMin][curMax], 
              f[l][r][min][max]
            );
          }
          int pow = (disc[max] - disc[min]) * (disc[max] - disc[min]);
          g[l][r] = std::min(
            g[l][r], 
            f[l][r][min][max] + a + b * pow
          );
        }
      }
    }
  }

  std::cout << g[0][n - 1];

  return 0;
}