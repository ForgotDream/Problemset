#include <iostream>
#include <string>

using i64 = long long;

constexpr int N = 1e5 + 50, mod = 998244353;
int n, q;
std::string s[N];
int a[N];
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
i64 f[N];
void solve() {
  init(1e5);
  std::cin >> n >> q;
  for (int i = 1; i <= n; i++) std::cin >> s[i];
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  for (int i = 1; i <= q; i++) {
    int opt;
    std::cin >> opt;
    if (!opt) {
      int u, v;
      std::cin >> u >> v;
    } else {
      int l, r;
      std::cin >> l >> r;
      i64 cur = 1;
      for (int i = l; i <= r; i++) (cur *= f[i]) %= mod;
      std::cout << cur << "\n";
    }
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
