#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

i64 k, x, a;

void solve() {
  std::cin >> k >> x >> a;
  i64 s = 1;
  for (int i = 2; i <= x + 1; i++) {
    i64 cur = std::ceil(1. * s / (k - 1));
    if (s % (k - 1) == 0) cur++;
    s += cur;
    if (s > a) break;
  }
  if (s > a) std::cout << "NO\n";
  else std::cout << "YES\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  std::cin >> t;
  while (t--) solve();

  return 0;
}


