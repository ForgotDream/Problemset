#include <algorithm>
#include <cstring>
#include <iostream>

using i64 = long long;

constexpr int N = 2e5 + 50;
int n, m;
i64 a[N], b[N];
void solve() {
  std::cin >> n >> m;
  a[1] = 1;
  for (int i = 2; i <= n; i++) std::cin >> a[i];
  for (int i = 1; i <= n; i++) std::cin >> b[i];
  std::sort(a + 1, a + n + 1), std::sort(b + 1, b + n + 1);
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    ans = std::max(ans, i - int(std::lower_bound(a + 1, a + n + 1, b[i]) - a - 1));
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
