/**
 * @file
 * @author  ForgotDream
 * @brief
 * @date    2023-10-16
 */
#include <cstring>
#include <cmath>
#include <iomanip>
#include <iostream>

using i64 = long long;
using f80 = double;

constexpr int N = 3e3 + 50;
int n;
f80 t[N], x[N], f[N][N];
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> t[i] >> x[i];
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= n; j++) f[i][j] = 1e18;
  }
  f[0][0] = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j <= i; j++) {
      f[i + 1][j] =
          std::min(f[i + 1][j],
                   std::max(f[i][j], abs(x[i + 1] - x[i]) / (t[i + 1] - t[i])));
      f[i + 1][i] =
          std::min(f[i + 1][i],
                   std::max(f[i][j], abs(x[i + 1] - x[j]) / (t[i + 1] - t[j])));
    }
  }
  f80 ans = 1e18;
  for (int i = 0; i <= n; i++) ans = std::min(ans, f[n][i]);
  std::cout << std::fixed << std::setprecision(9) << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
