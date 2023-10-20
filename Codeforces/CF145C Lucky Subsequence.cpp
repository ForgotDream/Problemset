/**
 * @file    CF145C Lucky Subsequence.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-10-19
 */
#include <iostream>
#include <map>

using i64 = long long;

constexpr int N = 1e5 + 50, mod = 1e9 + 7;
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
i64 C(i64 n, i64 m) {
  if (m > n) return 0;
  return fac[n] * ifc[m] % mod * ifc[n - m] % mod; 
}
// ------------------
int n, k, a[N], cnt[N], tot;
i64 f[N];
std::map<int, int> mp;
bool check(int num) {
  while (num) {
    if (num % 10 != 4 && num % 10 != 7) return false;
    num /= 10;
  }
  return true;
}
void solve() {
  std::cin >> n >> k;
  init(n);
  int all = n;
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i];
    if (check(a[i])) {
      if (!mp.count(a[i])) mp[a[i]] = ++tot;
      cnt[mp[a[i]]]++, all--;
    }
  }
  f[0] = 1;
  for (int i = 1; i <= tot; i++) {
    for (int j = tot; j; j--) f[j] = (f[j] + f[j - 1] * cnt[i]) % mod;
  }
  i64 ans = 0;
  for (int i = 0; i <= k; i++) (ans += f[i] * C(all, k - i)) %= mod;
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
