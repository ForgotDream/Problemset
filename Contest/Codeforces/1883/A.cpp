#include <cmath>
#include <iostream>

using i64 = long long;

void solve() {
  int ans = 0, pre = 1;
  for (int i = 1; i <= 4; i++) {
    char c;
    std::cin >> c;
    int cur = c - '0';
    if (!cur) cur = 10;
    // std::cerr << cur << " \n"[i == 4];
    ans += abs(cur - pre) + 1, pre = cur;
  }
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}
