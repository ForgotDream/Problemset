/**
 * @file    P4342 Polygon.cpp
 * @author  ForgotDream
 * @brief   Interval DP
 * @date    2023-06-02
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr i64 inf = 1e12;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  std::vector<i64> a(n);
  std::vector<bool> b(n);
  for (int i = 0; i < 2 * n; i++) {
    if (i & 1) {
      std::cin >> a[i / 2];
    } else {
      char c;
      std::cin >> c;
      b[i / 2] = (c == 't');
    }
  }

  auto calc = [](const std::vector<i64> &a, const std::vector<bool> &b) {
    int n = a.size();
    
    std::vector f(n, std::vector<i64>(n, -inf));
    std::vector g(n, std::vector<i64>(n, inf));
    for (int i = 0; i < n; i++) {
      g[i][i] = f[i][i] = a[i];
    }

    for (int len = 2; len <= n; len++) {
      for (int l = 0; l + len - 1 < n; l++) {
        int r = l + len - 1;
        for (int k = l; k < r; k++) {
          if (b[k]) {
            f[l][r] = std::max(f[l][r], f[l][k] + f[k + 1][r]);
            g[l][r] = std::min(g[l][r], g[l][k] + g[k + 1][r]);
          } else {
            f[l][r] = std::max({
              f[l][r], 
              f[l][k] * f[k + 1][r],
              f[l][k] * g[k + 1][r],
              g[l][k] * f[k + 1][r],
              g[l][k] * g[k + 1][r],
            });
            g[l][r] = std::min({
              g[l][r], 
              f[l][k] * f[k + 1][r],
              f[l][k] * g[k + 1][r],
              g[l][k] * f[k + 1][r],
              g[l][k] * g[k + 1][r],
            });
          }
        }
      }
    }

    return f[0][n - 1];
  };

  std::vector<int> v(n);
  for (int i = 0; i < n; i++) {
    std::vector<i64> cur = a;
    std::vector<bool> opt = b;
    std::rotate(cur.begin(), cur.begin() + i, cur.end());
    std::rotate(opt.begin(), opt.begin() + i, opt.end());
    opt.erase(opt.begin());
    v[i] = calc(cur, opt);
  }

  i64 max = *std::max_element(v.begin(), v.end());
  std::cout << max << "\n";
  for (int i = 0; i < n; i++) {
    if (v[i] == max) {
      std::cout << i + 1 << " ";
    }
  }
  std::cout << "\n";

  return 0;
}