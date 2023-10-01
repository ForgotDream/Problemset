#include <algorithm>
#include <iostream>

using i64 = long long;

constexpr int N = 105;
int n, x, a[N];
void solve() {
  std::cin >> n >> x;
  int cur = 0, max = 0, min = 101;
  for (int i = 1; i < n; i++) {
    std::cin >> a[i], cur += a[i];
    max = std::max(max, a[i]), min = std::min(min, a[i]);
  }
  cur -= max;
  if (cur >= x) {
    std::cout << 0 << "\n";
    return;
  }
  cur -= min;
  if (x - cur > 100) {
    std::cout << -1 << "\n";
    return;
  } else if (x - cur > max) {
    std::cout << -1 << "\n";
    return;
  }
  std::cout << x - cur << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
