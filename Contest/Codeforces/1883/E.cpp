#include <cstring>
#include <iostream>

using i64 = long long;
using f80 = long double;

constexpr int N = 2e5 + 50;
int n;
i64 a[N], f[N];
void solve() {
  std::cin >> n;
  i64 ans = 0;
  std::cin >> a[1];
  for (int i = 2; i <= n; i++) {
    std::cin >> a[i];
    int cur = 0;
    f80 cpy = a[i];
    while (cpy < a[i - 1]) cpy = 2 * cpy, cur++;
    cpy = a[i];
    while (cpy / 2>= a[i - 1]) cpy /= 2, cur--;
    f[i] = std::max(0ll, cur + f[i - 1]), ans += f[i];
    // std::cerr << f[i] << " \n"[i == n];
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
