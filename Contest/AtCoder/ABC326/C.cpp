#include <algorithm>
#include <iostream>

using i64 = long long;

constexpr int N = 3e5 + 50;
int n, m, a[N];
void solve() {
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  std::sort(a + 1, a + n + 1);
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    auto it = std::lower_bound(a + i, a + n + 1, a[i] + m);
    ans = std::max(ans, int(it - (a + i)));
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
