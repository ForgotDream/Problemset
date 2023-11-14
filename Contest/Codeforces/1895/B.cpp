#include <algorithm>
#include <iostream>

using i64 = long long;

constexpr int N = 205;
int n, a[N];
void solve() {
  std::cin >> n;
  for (int i = 1; i <= 2 * n; i++) std::cin >> a[i];
  std::sort(a + 1, a + 2 * n + 1);
  int ans = 0;
  for (int i = 2; i <= n; i++) {
    ans += (a[i] - a[i - 1]) + (a[i + n] - a[i + n - 1]);
  }
  std::cout << ans << "\n";
  for (int i = 1; i <= n; i++) {
    std::cout << a[i] << " " << a[i + n] << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}