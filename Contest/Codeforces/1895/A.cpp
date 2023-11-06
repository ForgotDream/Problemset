#include <iostream>

using i64 = long long;

int x, y, k;
void solve() {
  std::cin >> x >> y >> k;
  if (x >= y) return std::cout << x << "\n", void();
  std::cout << 2 * y - std::min(x + k, y) << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}