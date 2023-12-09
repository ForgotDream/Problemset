/**
 * @file    P3317 [SDOI2014] 重建.cpp
 * @author  ForgotDream
 * @brief   Matrix Tree Theorem
 * @date    2023-12-08
 */
#include <bits/stdc++.h>

using i64 = int64_t;
using f64 = double_t;

constexpr int N = 55;
constexpr f64 eps = 1e-8;
int n;
f64 a[N][N];
f64 det(f64 a[N][N]) {
  f64 res = 1;
  for (int i = 1; i < n; i++) {
    int p = -1;
    for (int j = i; j < n; j++) {
      if (std::abs(a[j][i]) > eps) {
        p = j;
        break;
      }
    }
    if (p == -1) return 0;
    res = res * a[p][p];
    if (i != p) std::swap(a[i], a[p]), res = -res;
    for (int j = i + 1; j < n; j++) a[i][j] /= a[i][i];
    for (int j = i + 1; j < n; j++) {
      if (std::abs(a[j][i]) <= eps) continue;
      for (int k = i + 1; k < n; k++) a[j][k] -= a[j][i] * a[i][k];
    }
  }
  return res;
}
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) std::cin >> a[i][j];
  f64 ans = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (i == j) continue;
      if (a[i][j] > 1 - eps) a[i][j] -= eps;
      if (i < j) ans *= (1 - a[i][j]);
      a[i][j] /= (1 - a[i][j]);
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (i == j) continue;
      a[i][i] += a[i][j], a[i][j] = -a[i][j];
    }
  }
  std::cout << std::fixed << std::setprecision(4) << ans * det(a) << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
