#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

int n;

void solve() {
  std::cin >> n;
  for (int i = 1; i <= 2 * n + 1; i++) {
    if (i & 1) std::cout << 1;
    else std::cout << 0;
  }
  std::cout << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
