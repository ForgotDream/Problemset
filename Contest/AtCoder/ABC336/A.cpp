#include <bits/stdc++.h>

using i64 = long long;

void solve() {
  int n;
  std::cin >> n;
  std::string ans = 'L' + std::string(n, 'o') + "ng";
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
