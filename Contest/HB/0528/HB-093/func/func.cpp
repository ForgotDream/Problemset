#include <bits/stdc++.h>

using i64 = long long;

constexpr int mod = 1e9 + 9;

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

signed main() {
  freopen("func.in", "r", stdin);
  freopen("func.out", "w", stdout);

  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int m, n;
  std::cin >> m >> n;

  std::vector<int> f(n + 1);
  f[0] = f[1] = 1;
  for (int i = 2; i <= n; i++) {
    (f[i] = f[i - 1] + f[i - 2]) %= mod;
  }

  if (m == 1) {
    std::cout << 1 << "\n";
    return 0;
  } else if (n < m) {
    std::cout << fastPow(2, n - 1, mod) << "\n";
    return 0;
  } else if (m == 2) {
    std::cout << f[n] << "\n";
    return 0;
  }

  std::vector<int> a(n + 1);
  a[0] = 0, a[1] = 1;
  for (int i = 2; i < m; i++) {
    a[i] = (2 * a[i - 1]) % mod;
  }
  for (int i = m; i <= n; i++) {
    a[i] = (1ll * (2 * a[i - 1] - (i == m ? 1 : a[i - m - 1])) + mod) % mod;
  }

  std::cout << a[n] << "\n";

  return 0;
}