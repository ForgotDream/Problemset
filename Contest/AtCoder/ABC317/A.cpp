#include <iostream>

using i64 = long long;

constexpr int N = 105;
int n, h, x, a[N];
void solve() {
  std::cin >> n >> h >> x;
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i];
    if (h + a[i] >= x) {
      std::cout << i << "\n";
      return;
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}