#include <iostream>

using i64 = long long;

int x, y;
void solve() {
  std::cin >> x >> y;
  if (x - y > 3 || y - x > 2) std::cout << "No\n"; 
  else std::cout << "Yes\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
