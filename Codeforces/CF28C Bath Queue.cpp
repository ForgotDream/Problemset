/**
 * @file    CF28C Bath Queue.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-08-23
 */
#include <cmath>
#include <iostream>
#include <iomanip>

using i64 = long long;
using f80 = long double;

constexpr int N = 55;
i64 c[N][N];
f80 C(int n, int m) { return c[n][m]; }
void init() {
  for (int i = 0; i <= 50; ++i) {
    for (int j = 0; j <= i; ++j) {
      if (!j) c[i][j] = 1;
      else c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
    }
  }
}

int n, m, a[N];
f80 f[N][N][N];
void solve() {
  init();
  std::cout << std::fixed << std::setprecision(20);
  std::cin >> n >> m;
  for (int i = 1; i <= m; ++i) std::cin >> a[i];
  f[0][0][0] = 1;
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j <= n; ++j) {
      for (int k = 0; k <= n; ++k) {
        if (f[i][j][k] == 0) continue;
        for (int l = 0; l + j <= n; ++l) {
          int len = std::max(k, int(std::ceil(1. * l / a[i + 1])));
          f[i + 1][j + l][len] += C(n - j, l) * f[i][j][k];
        }
      }
    }
  }
  f80 cnt = 0, sum = 0;
  for (int i = 0; i <= n; i++) cnt += f[m][n][i], sum += f[m][n][i] * i;
  std::cout << sum / cnt << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve();
  return 0;
}