#include <bits/stdc++.h>

using i64 = long long;

void solve() {
  int b, g;
  std::cin >> b >> g;

  if (b > g) std::cout << "Bat\n";
  else std::cout << "Glove\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
