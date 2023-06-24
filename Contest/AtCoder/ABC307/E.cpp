#include <bits/stdc++.h>

using i64 = long long;

constexpr int mod = 998244353;

i64 fastPow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  while (exp) {
    if (exp & 1) {
      (res *= base) %= mod;
    }
    (base *= base) %= mod;
    exp >>= 1;
  }
  return res;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  i64 n, m;
  std::cin >> n >> m;

  std::vector<i64> f(n), g(n);
  // f[i] -> answer
  f[0] = m, g[0] = g[1] = m;
  for (int i = 1; i < n; i++) {
    if (i >= 2) {
      (g[i] = (m - 1) * f[i - 2]) %= mod;
    }
    (f[i] = 1ll * m * fastPow(m - 1, i, mod) % mod - g[i] + mod) %= mod;
  }

  // for (int i = 0; i < n; i++) {
  //   std::cerr << f[i] << " " << g[i] << "\n";
  // }

  std::cout << f[n - 1] << "\n";

  return 0;
}