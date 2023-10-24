#include <algorithm>
#include <iostream>

using i64 = long long;

constexpr int N = 2e5 + 50;
int n, m, p, a[N], b[N];
i64 ans, sum[N];
void solve() {
  std::cin >> n >> m >> p;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  std::sort(a + 1, a + n + 1);
  for (int i = 1; i <= n; i++) sum[i] = sum[i - 1] + a[i];
  for (int i = 1; i <= m; i++) {
    std::cin >> b[i];
    int k = std::upper_bound(a + 1, a + n + 1, p - b[i]) - a - 1;
    ans += 1ll * k * b[i] + sum[k] + 1ll * (n - k) * p;
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
