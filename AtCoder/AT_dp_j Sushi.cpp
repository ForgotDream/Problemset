/**
 * @file    AT_dp_j Sushi.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-06-19
 */
#include <bits/stdc++.h>

using i64 = long long;
using f80 = long double;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout << std::fixed << std::setprecision(12);

  int n;
  std::cin >> n;

  std::vector<int> a(n);
  std::array<int, 4> cnt;
  cnt.fill(0);
  for (int i = 0; i < n; i++) { std::cin >> a[i], cnt[a[i]]++; }

  std::vector f(n + 1, std::vector(n + 1, std::vector<f80>(n + 1)));
  for (int k = 0; k <= n; k++) {
    for (int j = 0; j <= n; j++) {
      for (int i = 0; i <= n; i++) {
        if (!i && !j && !k) { continue; }
        int c = i + j + k;
        f[i][j][k] += 1. * n / c;
        if (i) { f[i][j][k] += i * f[i - 1][j][k] / c; }
        if (j && i != n) { f[i][j][k] += j * f[i + 1][j - 1][k] / c; }
        if (k && j != n) { f[i][j][k] += k * f[i][j + 1][k - 1] / c; }
      }
    }
  }

  std::cout << f[cnt[1]][cnt[2]][cnt[3]] << "\n";

  return 0;
}