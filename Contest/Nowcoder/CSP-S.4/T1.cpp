#include <iostream>

using i64 = long long;

constexpr int N = 3e5 + 50;
int n;
void solve() {
  std::cin >> n;
  i64 ans = n * (n - 1) * (n - 2) / 6, tmp = 0;
  for (int i = 1, u, v; i <= n; i++) {
    std::cin >> u >> v;
    tmp += 1ll * u * v;
  }
  std::cout << ans - tmp / 2 << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
