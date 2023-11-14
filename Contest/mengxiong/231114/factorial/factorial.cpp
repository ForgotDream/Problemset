#include <bits/stdc++.h>

using i64 = int64_t;

i64 m, p;
inline i64 fastPow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}
inline i64 inv(i64 u) { return fastPow(u, p - 2, p); }
void solve() {
  std::cin >> m >> p;
  if (p <= m) return std::cout << 0 << "\n", void();
  i64 ans = p - 1;
  for (auto i = p - 1; i > m; i--) ans = ans * inv(i) % p;
  std::cout << ans << "\n";
}

int main() {
  freopen("factorial.in", "r", stdin);
  freopen("factorial.out", "w", stdout);
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}
