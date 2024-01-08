#include <bits/stdc++.h>

using i64 = long long;

int n;

void solve() {
  std::cin >> n;
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= n - i; j++) {
      for (int k = 0; k <= n - i - j; k++) {
        std::cout << i << " " << j << " " << k << "\n";
      }
    }
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
