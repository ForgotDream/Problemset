#include <iostream>

using i64 = long long;

int x, k;
bool check(int u) {
  int cur = 0;
  while (u) cur += u % 10, u /= 10;
  return cur % k == 0;
}
void solve() {
  std::cin >> x >> k;
  while (!check(x)) x++;
  std::cout << x << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}
