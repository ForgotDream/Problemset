#include <iostream>

using i64 = long long;

constexpr int N = 500;
int n, a[N];
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  i64 ans = 0;
  for (int i = 0; i < (1 << n) - 1; i++) {
    if (__builtin_popcount(i) != n / 2) continue;
    i64 cur = 0;
    for (int j = 2; j <= n; j++) {
      int now = i & (1 << (j - 1));
      int pre = i & (1 << (j / 2 - 1));
      cur += a[j] * ((!!now) & (!!pre));
    }
    ans = std::max(ans, cur);
  }
  std::cout << ans << "\n";
}

int main() {
  std::freopen("still.in", "r", stdin);
  std::freopen("still.out", "w", stdout);
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
