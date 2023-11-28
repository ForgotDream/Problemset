/**
 * @file    P2455 [SDOI2006] 线性方程组.cpp
 * @author  ForgotDream
 * @brief   Gauss Jordan
 * @date    2023-11-22
 */
#include <bits/stdc++.h>

using i64 = int64_t;
using f80 = long double;

constexpr int N = 55;
int n;
f80 a[N][N];
int gaussJordan(f80 a[N][N]) {
  int cnt = 1;
  for (int i = 1; i <= n; i++) {
    int p = cnt;
    for (int j = cnt + 1; j <= n; j++) if (std::abs(a[j][i]) > std::abs(a[p][i])) p = j;
    if (a[p][i] == 0) continue;
    for (int j = 1; j <= n + 1; j++) std::swap(a[p][j], a[cnt][j]);
    for (int j = 1; j <= n; j++) {
      if (j == cnt) continue;
      f80 t = a[j][i] / a[cnt][i];
      for (int k = i + 1; k <= n + 1; k++) a[j][k] -= a[cnt][k] * t;
    }
    cnt++;
  }
  if (cnt > n) return 1;
  for (; cnt <= n; cnt++) if (a[cnt][n + 1] != 0) return -1;
  return 0;
}
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n + 1; j++) std::cin >> a[i][j];
  }
  auto d = gaussJordan(a);
  if (d != 1) return std::cout << d << "\n", void();
  for (int i = 1; i <= n; i++) {
    std::cout << "x" << i << "=" 
              << std::fixed << std::setprecision(2) << a[i][n + 1] / a[i][i] << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
