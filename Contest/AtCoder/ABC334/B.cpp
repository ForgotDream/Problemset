#include <bits/stdc++.h>

using i64 = long long;
using f96 = long double;

i64 a, l, r, m;

void solve() {
  std::cin >> a >> m >> l >> r;

  i64 lo = std::ceil(f96(l - a) / m);
  i64 hi = std::floor(f96(r - a) / m);

  std::cout << (hi - lo + 1) << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
