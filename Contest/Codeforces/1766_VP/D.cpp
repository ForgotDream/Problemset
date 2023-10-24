#include <cassert>
#include <cmath>
#include <iostream>
#include <numeric>

using i64 = long long;

constexpr int N = 1e7 + 50;
int prime[N], cnt, fac[N];
bool isNotPrime[N];
void getPrime(int n) {
  for (int i = 2; i <= n; i++) {
    if (!isNotPrime[i]) prime[++cnt] = i, fac[i] = i;
    for (int j = 1; j <= cnt && i * prime[j] <= n; j++) {
      isNotPrime[i * prime[j]] = true;
      fac[i * prime[j]] = prime[j];
      if (i % prime[j] == 0) break;
    }
  }
}
int x, y;
void solve() {
  std::cin >> x >> y;
  if (std::gcd(x, y) != 1) {
    std::cout << 0 << "\n";
    return;
  } else if (std::abs(x - y) == 1) {
    std::cout << -1 << "\n";
    return;
  } else if (x % 2 && y % 2) {
    std::cout << 1 << "\n";
    return;
  }
  int d = std::abs(x - y), ans = 1e9;
  while (d > 1) ans = std::min(ans, fac[d] - (x % fac[d])), d /= fac[d];
  std::cout << ans << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  getPrime(1e7);
  int t;
  std::cin >> t;
  while (t--) solve();
  return 0;
}