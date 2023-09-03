/**
 * @file    CF535D Tavas and Malekas.cpp
 * @author  ForgotDream
 * @brief   String + Hash
 * @date    2023-08-29
 */
#include <cstring>
#include <iostream>

using i64 = long long;

namespace HASH {
using u64 = unsigned long long;
constexpr int N = 1e6 + 50;
constexpr u64 base = 114514;
struct Hash {
  u64 hash[N], pw[N];
  void init(char *s, int n) {
    pw[0] = 1;
    for (int i = 1; i <= n; i++) {
      hash[i] = hash[i - 1] * base + *(s + i);
      pw[i] = pw[i - 1] * base;
    }
  }
  u64 operator()(int l, int r) { return hash[r] - hash[l - 1] * pw[r - l + 1]; }
} hash;
}
constexpr int N = 1e6 + 50, mod = 1e9 + 7;
int n, m, n, a[N], d[N];
char s[N];
i64 fastPow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}
void solve() {
  std::cin >> n >> m >> (s + 1);
  n = std::strlen(s + 1);
  HASH::hash.init(s, n);
  for (int i = 1; i <= m; i++) std::cin >> a[i];
  if (m) d[a[1]]++, d[a[1] + n]--;
  for (int i = 2; i <= m; i++) {
    d[a[i]]++, d[a[i] + n]--;
    if (a[i] > a[i - 1] + n - 1) continue;
    int tmp = a[i - 1] + n - a[i];
    if (HASH::hash(n - tmp + 1, n) != HASH::hash(1, tmp)) {
      std::cout << 0 << "\n";
      return;
    }
  }
  for (int i = 1; i <= n; i++) d[i] += d[i - 1];
  int cnt = 0;
  for (int i = 1; i <= n; i++) {
    if (!d[i]) cnt++;
  }
  std::cout << fastPow(26, cnt, mod) << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}