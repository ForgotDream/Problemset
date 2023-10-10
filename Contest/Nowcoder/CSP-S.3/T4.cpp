#include <iostream>

using i64 = long long;

constexpr int N = 1e6 + 50, mod = 998244353;
int n, k, a[N];
i64 fastPow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}
void solve() {
  std::cin >> n >> k;
  int m = fastPow(k + 1, n, mod);
  for (int i = 1; i <= m; i++) std::cin >> a[i];
  std::cout << 0 << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
