#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e5 + 50;

int n, a[N];

void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i];

  i64 ans = 0;
  for (int i = n - 1; i >= 1; i--) {
    if (a[i + 1] >= a[i]) continue;
    int d = (a[i] - 1) / a[i + 1] + 1;
    a[i] = a[i] / d, ans += d - 1;
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
