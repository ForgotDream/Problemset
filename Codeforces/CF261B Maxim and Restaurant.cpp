/**
 * @file    CF261B Maxim and Restaurant.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-08-16
 */
#include <bits/stdc++.h>
using i64 = long long;
using f80 = long double;
constexpr int N = 55;
int n, a[N], p, sum;
f80 f[N][N][N], bfac[N], ans;
void init() {
  bfac[0] = 1;
  for (int i = 1; i <= n; i++) bfac[i] = i * bfac[i - 1];
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout << std::fixed << std::setprecision(12);
  std::cin >> n;
  init();
  for (int i = 1; i <= n; i++) std::cin >> a[i], sum += a[i];
  std::cin >> p;
  if (sum <= p) return std::cout << n << "\n", 0;
  for (int u = 1; u <= n; u++) {
    std::memset(f, 0, sizeof(f));
    f[0][0][0] = 1;
    for (int i = 1; i <= n; i++) {
      for (int j = 0; j <= i; j++) {
        for (int k = 0; k <= p; k++) {
          f[i][j][k] = f[i - 1][j][k];
          if (i == u) continue;
          if (k >= a[i] && j) f[i][j][k] += f[i - 1][j - 1][k - a[i]];
        }
      }
    }
    for (int i = 1; i < n; i++) {
      for (int j = std::max(0, p - a[u] + 1); j <= p; j++) {
        ans += i * bfac[i] * bfac[n - i - 1] * f[n][i][j];
      }
    }
  }
  std::cout << ans / bfac[n] << "\n";
  return 0;
}