#include <bits/stdc++.h>

using i64 = long long;

void solve() {
  int n;
  std::cin >> n;

  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  if (n == 1) {
    std::cout << 0 << "\n";
    return;
  } else if (*std::max_element(a.begin(), a.end()) == 0) {
    std::cout << 0 << "\n";
    return;
  }

  int ans = 0;
  for (int i = 0; i < n / 2; i++) {
    ans = std::gcd(ans, std::abs(a[i] - a[n - i - 1]));
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