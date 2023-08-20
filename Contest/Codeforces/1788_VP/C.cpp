#include <iostream>
#include <cmath>

using i64 = long long;
using pii = std::pair<int, int>;

int t, n;

void solve() {
  std::cin >> n;
  if (n % 2 == 0) return void(std::cout << "No\n");
  std::cout << "Yes\n";
  int lim = std::ceil(n / 2.);
  for (int i = 1; i <= lim; i++) {
    std::cout << i << " " << 2 * n - lim + i << "\n";
  }
  int len = n - lim;
  for (int i = lim + 1; i <= n; i++) {
    std::cout << i << " " << i + len << "\n";
  }
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> t;

  while (t--) solve();

  return 0;
}