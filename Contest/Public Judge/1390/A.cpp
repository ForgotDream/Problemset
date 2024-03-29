#include <iostream>

using i64 = long long;

constexpr int N = 1e6 + 50, M = 60;
int n;
i64 a[N], f[N], g[M];
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < 60; j++) {
      if (g[j]) f[i] = std::max(f[i], f[g[j]] + (a[i] & a[g[j]]));
      if (a[i] & (1ll << j)) g[j] = i;
    }
  }
  i64 ans = 0;
  for (int i = 1; i <= n; i++) ans = std::max(ans, f[i]);
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
