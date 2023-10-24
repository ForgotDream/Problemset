/**
 * @file    P4548 [CTSC2006] 歌唱王国.cpp
 * @author  ForgotDream
 * @brief   KMP + PGF
 * @date    2023-09-20
 */
#include <cstring>
#include <iomanip>
#include <iostream>

using i64 = long long;

constexpr int N = 1e5 + 50, mod = 1e4;
int n, m, a[N];
int nxt[N];
void kmp() {
  std::memset(nxt, 0, sizeof(nxt));
  for (int i = 2; i <= n; i++) {
    int j = nxt[i - 1];
    while (j && a[i] != a[j + 1]) j = nxt[j];
    if (a[i] == a[j + 1]) j++;
    nxt[i] = j;
  }
}
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
  kmp();
  i64 ans = 0;
  int p = n;
  while (p) {
    ans = (ans + fastPow(m, p, mod)) % mod;
    p = nxt[p];
  }
  std::cout << std::setfill('0') << std::setw(4) << ans % mod << "\n";
}

signed main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  std::cin >> m >> t;
  m %= mod;
  while (t--) solve();
  return 0;
}
