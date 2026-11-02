#include <bits/stdc++.h>

using i64 = long long;

void solve() {
  int n;
  std::cin >> n;

  i64 ans = 0, sum = 0;
  for (int i = 0, u; i < n; i++) {
    std::cin >> u;
    ans += 1ll * i * u - sum;
    sum += u;
  }

  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
