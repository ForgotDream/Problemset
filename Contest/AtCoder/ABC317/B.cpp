#include <algorithm>
#include <iostream>

using i64 = long long;

constexpr int N = 105;
int n, a[N];
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  std::sort(a + 1, a + n + 1);
  for (int i = 2; i <= n; i++) {
    if (a[i] != a[i - 1] + 1) {
      std::cout << a[i - 1] + 1 << "\n";
      return;
    }
  }
  std::cout << n + 1 << "\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}