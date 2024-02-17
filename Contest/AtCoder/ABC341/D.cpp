#include <bits/stdc++.h>

using i64 = long long;
using i128 = __int128;
using u32 = unsigned;

int n, m;
i64 k;

i128 calc(i128 u, i128 n, i128 m) {
  i128 tmp = u;
  tmp += u * n / m;
  tmp -= u / m * 2;
  return tmp;
}

void solve() {
  std::cin >> n >> m >> k;
  if (n > m) std::swap(n, m);

  i64 g = std::gcd(n, m);
  i64 lo = 0, hi = 1e12;
  n /= g, m /= g;

  while (lo < hi) {
    i64 mid = (lo + hi) / 2;
    if (calc(mid, n, m) < (i128)k) lo = mid + 1;
    else hi = mid;
  }

  i128 res = calc(lo, n, m);
  if (res == k) {
    std::cout << n * lo * g << "\n";
    return;
  }

  lo = 0, hi = 1e12;
  while (lo < hi) {
    i64 mid = (lo + hi) / 2;
    if (calc(mid, m, n) < k) lo = mid + 1;
    else hi = mid;
  }
  std::cout << m * lo * g << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
