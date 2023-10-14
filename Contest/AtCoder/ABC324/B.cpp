#include <iostream>

using i64 = long long;

i64 n;
void solve() {
  std::cin >> n;
  while (n % 2 == 0) n /= 2;
  while (n % 3 == 0) n /= 3;
  if (n != 1) std::cout << "No\n";
  else std::cout << "Yes\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
