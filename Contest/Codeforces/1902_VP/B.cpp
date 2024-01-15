#include <bits/stdc++.h>

using i64 = long long;

int n, l, t;
i64 p;

inline i64 calc(i64 u) {
  i64 tmp = u * t + (u / 2) * l;
  if (tmp >= p) return u / 2;
  i64 res = (p - tmp - 1) / l + (u / 2) + 1;
  return res;
}

void solve() {
  std::cin >> n >> p >> l >> t;

  i64 ans = 1e18, cnt = (n - 1) / 7 + 1;
  int lo = 0, hi = cnt;

  // std::cerr << hi << "\n";
  while (lo <= hi) {
    int m1 = lo + (hi - lo) / 3, m2 = hi - (hi - lo) / 3;
    if (calc(m1) >= calc(m2)) {
      lo = m1 + 1;
      ans = std::min(ans, calc(m2));
    } else {
      hi = m2 - 1;
      ans = std::min(ans, calc(m1));
    }
  }

  std::cout << n - ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  std::cin >> t;
  while (t--) solve();

  return 0;
}
