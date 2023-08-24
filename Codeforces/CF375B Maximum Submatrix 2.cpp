/**
 * @file    CF375B Maximum Submatrix 2.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-08-22
 */
#include <algorithm>
#include <iostream>

using i64 = long long;

constexpr int N = 5050;
int n, m, a[N][N], f[N][N], tmp[N];
void solve() {
  std::cin >> n >> m;
  bool flg = false;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      char c;
      std::cin >> c;
      a[i][j] = c - '0', flg |= a[i][j];
    }
  }
  if (!flg) {
    std::cout << "0\n";
    return;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = m; j >= 1; j--) {
      if (a[i][j]) f[i][j] = f[i][j + 1] + 1;
    }
  }
  int ans = 0;
  for (int j = 1; j <= m; j++) {
    for (int i = 1; i <= n; i++) tmp[i] = f[i][j];
    std::sort(tmp + 1, tmp + n + 1);
    for (int i = 1; i <= n; i++) ans = std::max(ans, tmp[i] * (n - i + 1));
  }
  std::cout << ans << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve();
  return 0;
}