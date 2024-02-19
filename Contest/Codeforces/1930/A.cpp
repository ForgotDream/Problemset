#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 105;

int n, a[N];

void solve() {
  std::cin >> n;
  for (int i = 1; i <= 2 * n; i++) std::cin >> a[i];

  std::sort(a + 1, a + 2 * n + 1);
  i64 ans = 0;
  for (int i = 1; i <= 2 * n; i += 2) ans += a[i];
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  std::cin >> t;
  while (t--) solve();

  return 0;
}
