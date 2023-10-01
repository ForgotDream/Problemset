#include <iostream>

using i64 = long long;

constexpr int N = 1e6 + 50;
i64 n, p;
i64 fac[N], ifc[N];
i64 fastPow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}
void init(i64 n, i64 mod) {
  fac[0] = ifc[0] = 1;
  for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod;
  ifc[n] = fastPow(fac[n], mod - 2, mod);
  for (int i = n - 1; i; i--) ifc[i] = (i + 1) * ifc[i + 1] % mod;
}
i64 C(i64 n, i64 m) {
  if (n < m) return 0ll;
  return fac[n] * ifc[m] % p * ifc[n - m] % p;
}
i64 lucas(i64 n, i64 m) {
  if (!m) return 1;
  return C(n % p, m % p) * lucas(n / p, m / p);
}
i64 f[N], g[N], h[N];
void solve() {
  std::cin >> n >> p;
  init(p - 1, p);
  if (n <= 1e6) {
    i64 ans = 0, inv2 = (p + 1) / 2;
    ans = fastPow(3, n, p) % p;
    for (int i = 0; i <= n / 2; i++) {
      (ans -= lucas(2 * i, i) * lucas(n, 2 * i) % p - p) %= p;
    }
    std::cout << inv2 * (ans + p) % p << "\n";
    return;
  }
  i64 ans = 0, inv2 = (p + 1) / 2;
  ans = fastPow(3, n, p);
  for (int i = 0; i < p; i++) {
    f[i] = lucas(2 * i, i);
    g[i] = (f[i] + (i ? g[i - 1] : 0)) % p;
  }
  i64 tmp = 0, half = n / 2 + 1;
  tmp = inv2 * (half / p + 1) % p * (half / p) % p * g[p - 1] % p;
  for (int i = 0; i < half % p; i++) {
    (tmp += f[i] * (half / p + 1) % p) %= p;
  }
  std::cout << inv2 * (ans - tmp + p) % p << "\n";
}

int main() {
  std::freopen("vote.in", "r", stdin);
  std::freopen("vote.out", "w", stdout);
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}