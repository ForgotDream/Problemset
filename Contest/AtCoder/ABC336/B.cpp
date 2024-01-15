#include <bits/stdc++.h>

using i64 = long long;

void solve() {
  int n;
  std::cin >> n;
  std::cout << __builtin_ctz(n) << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
