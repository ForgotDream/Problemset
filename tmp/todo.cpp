/**
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2023-10-18
 */
#include <iostream>

using i64 = long long;

constexpr int N = 2050, mod = 1e9 + 7;
int n, a[4][N];
int f[N][N][2];
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
void solve() {
  std::cin >> n;
  for (int i = 1; i <= 3; i++) {
    for (int j = 1; j <= n; j++) {
      char c;
      std::cin >> c, a[i][j] = c == 'o';
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
