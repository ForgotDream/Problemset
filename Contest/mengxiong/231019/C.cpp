#include <iostream>

using i64 = long long;

constexpr int N = 1e5 + 50, mod = 1e9 + 7;
int n, m, x[N], a[N];
i64 k;
i64 fastPow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> x[i];
  std::cin >> m >> k;
  for (int i = 1; i <= m; i++) std::cin >> a[i];
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
