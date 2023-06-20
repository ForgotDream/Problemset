/**
 * @file    AT_dp_h Grid 1.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-06-18
 */
#include <bits/stdc++.h>

using i64 = long long;

const int mod = 1e9 + 7;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int h, w;
  std::cin >> h >> w;

  std::vector a(h, std::vector<int>(w));
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      char c;
      std::cin >> c;
      a[i][j] = (c == '.');
    }
  }

  std::vector f(h, std::vector<i64>(w));
  f[0][0] = a[0][0];
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      if (!a[i][j]) { continue; }
      if (i) { (f[i][j] += f[i - 1][j]) %= mod; }
      if (j) { (f[i][j] += f[i][j - 1]) %= mod; }
    }
  }
  std::cout << f[h - 1][w - 1] << "\n";

  return 0;
}