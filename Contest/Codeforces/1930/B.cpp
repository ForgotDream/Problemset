#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

int n;

void solve() {
  std::cin >> n;
  int p = n + 1, q = 0;
  for (int i = 1; i <= n; i++) {
    if (i & 1) std::cout << ++q << " ";
    else std::cout << --p << " ";
  }
  std::cout << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  std::cin >> t;
  while (t--) solve();

  return 0;
}
