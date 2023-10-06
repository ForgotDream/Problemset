/**
 * @file
 * @author  ForgotDream
 * @brief
 * @date    2023-10-06
 */
#include <iostream>

using i64 = long long;

constexpr int N = 1e5 + 50;
int n, k;
i64 a[N];
namespace N_LESS_THAN_100 {
constexpr int N = 105;
constexpr i64 inf = 1e18;
i64 f[N][N];
=======
void solve() {
  for (int i = 1; i <= n; i++) a[i] = a[i - 1] + a[i];
  f[0][0] = -inf;
  for (int i = 1; i <= k; i++) {
    for (int j = i; j <= n; j++) {
      f[i][j] = inf;
      for (int k = i - 1; k < j; k++) {
        f[i][j] = std::min(f[i][j], std::max(f[i - 1][k], a[j] - a[k]));
      }
    }
  }
  i64 ans = inf;
  for (int i = k; i <= n; i++) ans = std::min(ans, f[k][i]);
  std::cout << ans << "\n";
}
}  // namespace N_LESS_THAN_100
namespace K_EQUALS_TO_1 {
constexpr i64 inf = 1e18;
void solve() {
  i64 ans = inf;
  for (int i = 1; i <= n; i++) {
    a[i] = a[i - 1] + a[i], ans = std::min(ans, a[i]);
  }
  std::cout << ans << "\n";
}
}  // namespace K_EQUALS_TO_1
namespace ALL_PERFECT {
constexpr i64 inf = 1e18;
i64 f[2][N];
void solve() {
  for (int i = 1; i <= n; i++) a[i] = a[i - 1] + a[i];
  int cur = 0, pre = 1;
  f[cur][0] = -inf;
  for (int i = 1; i <= k; i++) {
    cur ^= 1, pre ^= 1;
    for (int j = i; j <= n; j++) {
      f[cur][j] = inf;
      for (int k = i - 1; k < j; k++) {
        f[cur][j] = std::min(f[cur][j], std::max(f[pre][k], a[j] - a[k]));
      }
    }
  }
  i64 ans = inf;
  for (int i = k; i <= n; i++) ans = std::min(ans, f[cur][i]);
  std::cout << ans << "\n";
}
}  // ALL_PERFECT
void solve() {
  std::cin >> n >> k;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  if (n <= 100) N_LESS_THAN_100::solve();
  else if (k == 1) K_EQUALS_TO_1::solve();
  else ALL_PERFECT::solve();
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}
