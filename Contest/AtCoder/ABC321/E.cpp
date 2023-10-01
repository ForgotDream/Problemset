#include <cmath>
#include <iostream>

using i64 = long long;
using i128 = __int128;

i64 n, x, k;
int mdep;
int dep(i64 num) { return 64 - __builtin_clzll(num); }
i64 calc(i64 u, i64 k) {
  if (k < 0) return 0;
  int d = dep(u);
  if (d + k < mdep) {
    return 1ll << k;
  } else if (d + k == mdep) {
    i64 nxt = u << k;
    return std::max(std::min(n, nxt + (1ll << k) - 1) - nxt + 1, 0ll);
  } else {
    return 0;
  }
}
void solve() {
  std::cin >> n >> x >> k;
  mdep = dep(n);
  if (!k) {
    std::cout << 1 << "\n";
    return;
  }
  i64 ans = calc(x, k);
  while ((x >> 1) && k) {
    ans += calc(x >> 1, k - 1) - calc(x, k - 2);
    x >>= 1, k--;
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
