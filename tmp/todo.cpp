/**
 * @file
 * @author  ForgotDream
 * @brief
 * @date    2023-10-12
 */
#include <iostream>

using i64 = long long;

constexpr int N = 1e3 + 50, M = 150;
int n, a[N][3];
i64 f[N][M][M][3];
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i][0] >> a[i][1] >> a[i][2];
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= std::min(M, i); j++) {
      for (int k = j; k <= std::min(M, i - j); k++) {
        if (j == 1 && k == 1) continue;
        if (j != 1) {
          for (int d = 0; d < 3; d++) {
            f[i][j][k][d] = std::max(
                f[i][j][k][d], f[i - 1][j - 1][k - 1][d] + a[i][d] - 2 * i);
          }
        } else {
          for (int d1 = 0; d1 < 3; d1++) {
            for (int d2 = 0; d2 < 3; d2++) {
              if (j == 1 && d1 == d2) continue;
              f[i][j][k][d1] = std::max(f[i - 1][])
            }
          }
        }
      }
    }
  }
  i64 ans = 0;
  for (int i = 0; i <= std::min(M, n); i++) {
    for (int j = 0; j <= std::min(M, n - i); j++) {
      if (!i && !j) continue;
      for (int k = 1; k <= 3; k++) ans = std::max(ans, f[n][i][j]);
    }
  }
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}
