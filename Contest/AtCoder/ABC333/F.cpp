#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 3050, mod = 998244353;
int n, f[N][N];
i64 fastPow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}
i64 inv(i64 u) { return fastPow(u, mod - 2, mod); }
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cout << f[i][1] << " \n"[i == n];
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
