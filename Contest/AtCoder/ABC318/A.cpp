#include <iostream>

using i64 = long long;

int n, m, p;
void solve() {
  std::cin >> n >> m >> p;
  if (m > n) {
    std::cout << 0 << "\n";
    return;
  }
  int ans = 1;
  n -= m;
  ans += n / p;
  std::cout << ans << "\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}