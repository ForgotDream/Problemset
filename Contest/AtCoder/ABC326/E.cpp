#include <iostream>

using i64 = long long;

constexpr int N = 3e5 + 50, mod = 998244353;
int n, a[N];
i64 f[N], g[N];
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
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  i64 invn = fastPow(n, mod - 2, mod), inv2 = fastPow(2, mod - 2, mod);
  i64 ans = 0;
  for (int i = 1; i <= n; i++) {
    i64 d = (n - f[i - 1] + mod) * invn % mod;
    f[i] = (n + f[i - 1] + 1) * inv2 % mod;
    // g[i] = (g[i - 1] + d * a[i] % mod) % mod;
    g[i] = d * (a[i] + g[i - 1]) % mod;
    ans = (ans + (1 - d + mod) * g[i - 1] % mod) % mod;
    std::cout << d << " " << f[i] << " " << g[i] << "\n";
  }
  std::cout << (ans + g[n]) % mod << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
