#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

int n, k;

void solve() {
  std::cin >> n >> k;

  if (k <= 4 * n - 4) {
    std::cout << (k + 1) / 2 << "\n";
  } else {
    k -= 4 * n - 4;
    std::cout << 2 * n - 2 + k << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  std::cin >> t;
  while (t--) solve();

  return 0;
}

