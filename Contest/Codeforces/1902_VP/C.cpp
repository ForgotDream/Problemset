#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e5 + 50;

int n, a[N], d[N];

void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i];

  int mx = *std::max_element(a + 1, a + n + 1);
  for (int i = 1; i <= n; i++) d[i] = mx - a[i];
  std::sort(d + 1, d + n + 1);

  int ans = 0;
  for (int i = 1; i <= n; i++) {
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
