#include <iostream>

using i64 = long long;

int n;
void solve() {
  std::cin >> n;
  std::cout << 1;
  for (int i = 1; i <= n; i++) {
    bool flg = false;
    for (int j = 1; j <= 9; j++) {
      if (n % j == 0 && i % (n / j) == 0) {
        std::cout << j, flg = true;
        break;
      }
    }
    if (!flg) std::cout << "-";
  }
  std::cout << "\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}