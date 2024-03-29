#include <bits/stdc++.h>

using i64 = long long;

void solve() {
  int n;
  std::cin >> n;

  std::vector<int> a(n + 1);
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i];
  }

  for (int i = 1; i <= n; i++) {
    ans = std::gcd(ans, std::abs(a[i] - i));
  }

  std::cout << ans << "\n";

  return;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int t;
  std::cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}