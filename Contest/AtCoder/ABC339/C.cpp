#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 2e5 + 50;
int n, a[N];

void solve() {
  std::cin >> n;

  i64 ans = 0, s = 0;
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i], s += a[i];
    if (s < 0) ans -= s, s = 0;
  }

  for (int i = 1; i <= n; i++) ans += a[i];
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
