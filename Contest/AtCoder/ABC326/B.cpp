#include <iostream>

using i64 = long long;

int n;
bool check(int u) {
  int a = u % 10;
  u /= 10;
  int b = u % 10;
  u /= 10;
  int c = u % 10;
  u /= 10;
  return b * c == a;
}
void solve() {
  std::cin >> n;
  while (!check(n)) n++;
  std::cout << n << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
