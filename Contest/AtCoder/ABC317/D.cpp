#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>

using i64 = long long;

constexpr int N = 105, M = 1e5 + 50;
int n, x[N], y[N], z[N];
int a[N];
i64 f[N][M], sum;
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> x[i] >> y[i] >> z[i], sum += z[i];
  for (int i = 1; i <= n; i++) {
    if (y[i] > x[i]) {
      a[i] = std::ceil((x[i] + y[i]) / 2.) - x[i];
    }
    std::cerr << a[i] << "\n";
  }
  std::memset(f, 0x3f, sizeof(f));
  f[0][0] = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < z[i]; j++) f[i][j] = f[i - 1][j];
    for (int j = z[i]; j <= sum; j++) {
      f[i][j] = std::min(f[i - 1][j], f[i - 1][j - z[i]] + a[i]);
    }
  }
  i64 ans = 0x3f3f3f3f3f3f3f3f;
  for (int i = std::ceil(sum / 2.); i <= sum; i++) {
    ans = std::min(ans, f[n][i]);
  }
  std::cout << ans << "\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}