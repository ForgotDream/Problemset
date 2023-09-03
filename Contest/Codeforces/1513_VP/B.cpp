#include <algorithm>
#include <iostream>

using i64 = long long;

constexpr int N = 2e5 + 50, mod = 1e9 + 7;
i64 fac[N], ifc[N];
i64 fastPow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}
void init(int n) {
  fac[0] = ifc[0] = 1;
  for (int i = 1; i <= n; i++) fac[i] = i * fac[i - 1] % mod;
  ifc[n] = fastPow(fac[n], mod - 2, mod);
  for (int i = n - 1; i >= 1; i--) ifc[i] = ifc[i + 1] * (i + 1) % mod;
}
i64 C(int n, int m) { return fac[n] * ifc[m] % mod * ifc[n - m] % mod; }

int n, a[N];
void solve() {
  std::cin >> n;
  int cnt = 0;
  for (int i = 1; i <= n; i++) std::cin >> a[i], cnt += !a[i];
  if (cnt == 1) {
    std::cout << 0 << "\n";
    return;
  } else if (cnt >= 2) {
    std::cout << 2 * C(cnt, 2) % mod * fac[n - 2] % mod << "\n";
    return;
  }
  int k = a[1];
  for (int i = 2; i <= n; i++) k &= a[i];
  int c = std::count(a + 1, a + n + 1, k);
  std::cout << 1ll * c * (c - 1) % mod * fac[n - 2] % mod << "\n";
}

int main() {
  std::cin.tie(nullptr);
  std::ios::sync_with_stdio(false);
  init(2e5);
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}