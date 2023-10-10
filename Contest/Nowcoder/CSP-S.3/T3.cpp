#include <iostream>
#include <string>

using i64 = long long;

constexpr int N = 1e5 + 50, mod = 998244353;
// --- Comb Utils ---
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
  for (int i = n - 1; i; i--) ifc[i] = (i + 1) * ifc[i + 1] % mod;
}
i64 C(i64 n, i64 m) { return fac[n] * ifc[m] % mod * ifc[n - m] % mod; }
// ------------------
std::string s;
int n;
void solve() {
  std::cin >> s;
  n = s.length(), init(n);
  i64 ans = 0, val = 0;
  s = " " + s;
  for (int i = 1; i <= n; i++) {
    int d = s[i] - '0';
    val = (10 * val + d) % mod;
    ans += d * fastPow(2, i - 1, mod) % mod * fastPow(11, n - i, mod) % mod;
  }
  std::cout << (ans * 2 % mod - val + mod) % mod << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
