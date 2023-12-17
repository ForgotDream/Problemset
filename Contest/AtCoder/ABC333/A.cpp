#include <bits/stdc++.h>

using i64 = long long;

int n;
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cout << n;
  std::cout << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
