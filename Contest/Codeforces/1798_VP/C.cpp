#include <iostream>
#include <numeric>

using i64 = long long;

constexpr int N = 2e5 + 50;
int t, n;
i64 a[N], b[N];

void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i] >> b[i], a[i] *= b[i];

  int i = 1, ans = 0;
  while (i <= n) {
    ans++;
    i64 gcd = a[i], lcm = b[i];
    int j = i + 1;
    while (j <= n) {
      gcd = std::gcd(gcd, a[j]);
      if (gcd < lcm) break;
      lcm = std::lcm(lcm, b[j]);
      if (gcd % lcm != 0) break;
      j++;
    }
    i = j;
  }

  std::cout << ans << "\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> t;

  while (t--) solve();

  return 0;
}