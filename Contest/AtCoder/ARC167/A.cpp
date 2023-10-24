#include <algorithm>
#include <iostream>

using i64 = long long;

constexpr int N = 2e5 + 50;
int n, m;
i64 a[N];
void solve() {
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  std::sort(a + 1, a + n + 1);
  i64 ans = 0;
  for (int i = 1; i <= (n - m); i++) {
    ans += (a[i] + a[2 * (n - m) - i + 1]) * (a[i] + a[2 * (n - m) - i + 1]);
  }
  for (int i = 2 * (n - m) + 1; i <= n; i++) ans += a[i] * a[i];
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
