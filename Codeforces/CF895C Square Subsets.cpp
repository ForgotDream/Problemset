/**
 * @file    CF895C Square Subsets.cpp
 * @author  ForgotDream
 * @brief   Linear Basis
 * @date    2023-08-30
 */
#include <iostream>

using i64 = long long;

namespace VECSPACE {
constexpr int N = 32;
int p[N], cnt;
void insert(int val) {
  for (int i = N - 1; ~i; i--) {
    if (!(val & (1ll << i))) continue;
    if (!p[i]) {
      p[i] = val, cnt++;
      break;
    }
    val ^= p[i];
  }
}
}
constexpr int N = 1e5 + 50, mod = 1e9 + 7;
int n, a[N];
int p[] = {2,  3,  5,  7,  11, 13, 17, 19, 23, 29,
           31, 37, 41, 43, 47, 53, 59, 61, 67},
    cnt = 19;
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
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i];
    int cur = 0;
    for (int j = 0; j < cnt; j++) {
      int cnt = 0;
      while (a[i] % p[j] == 0) a[i] /= p[j], cnt ^= 1;
      cur ^= cnt << j;
    }
    VECSPACE::insert(cur);
  }
  for (int i = cnt - 1; ~i; i--) {
    if (VECSPACE::p[i]) n--;
  }
  std::cout << (fastPow(2, std::max(n, 0), mod) - 1 + mod) % mod << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}