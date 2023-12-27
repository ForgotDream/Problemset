/*
 * @file    CF1909F2 F2 Small Permutation Problem (Hard Version).cpp
 * @author  ForgotDream
 * @brief   Ad Hoc
 * @date    2023-12-24
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e5 + 50, mod = 998244353;
int n, a[N];

i64 fac[N], ifc[N];
i64 fast_pow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}
i64 get_inv(i64 u) { return fast_pow(u, mod - 2, mod); }
void init(int n) {
  fac[0] = ifc[0] = 1;
  for (int i = 1; i <= n; i++) fac[i] = i * fac[i - 1] % mod;
  ifc[n] = get_inv(fac[n]);
  for (int i = n - 1; i; i--) ifc[i] = (i + 1) * ifc[i + 1] % mod;
}
inline i64 C(i64 n, i64 m) { 
  if (m > n) return 0;
  return fac[n] * ifc[m] % mod * ifc[n - m] % mod; 
}

inline i64 calc(int h, int w, int k) {
  return C(h, k) * C(w, k) % mod * fac[k] % mod;
}

void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i];

  if (a[n] != n && a[n] != -1) return std::cout << 0 << "\n", void();

  int p = 0;
  i64 ans = 1;
  for (int i = 1; i <= n; i++) {
    if (a[i] == -1) continue;

    int d = a[i] - a[p];
    if (d < 0) return std::cout << 0 << "\n", void();

    i64 cur = 0;
    for (int k = 0; k <= d; k++) {
      cur = (cur + calc(i - p, i - a[p] - k, d - k) % mod * calc(i - p, p - a[p], k) % mod) % mod;
    }
    // std::cerr << n << " " << cur << "\n";
    ans = ans * cur % mod, p = i;
  }
  
  int d = n - a[p];
  i64 cur = 0;
  for (int k = 0; k <= d; k++) {
    cur = (cur + calc(n - p, n - a[p] - k, d - k) % mod * calc(n - p, p - a[p], k) % mod) % mod;
  }
  ans = ans * cur % mod;

  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  init(2e5);

  int t = 1;
  std::cin >> t;
  while (t--) solve();

  return 0;
}
