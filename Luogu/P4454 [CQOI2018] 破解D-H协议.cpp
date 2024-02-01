/*
 * @file    P4454 [CQOI2018] 破解D-H协议.cpp
 * @author  ForgotDream
 * @brief   BSGS
 * @date    2024-02-01
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

i64 g, P;
int n;

i64 fast_pow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}

i64 bsgs(i64 a, i64 b, i64 p) {
  std::unordered_map<i64, i64> mp;
  i64 cur = 1, t = std::sqrt(p) + 1;
  for (int B = 1; B <= t; B++) {
    cur = cur * a % p;
    mp[b * cur % p] = B;
  }
  i64 now = cur;
  for (int A = 1; A <= t; A++) {
    if (mp[now]) return A * t - mp[now];
    now = now * cur % p;
  }
  return -1;
}

void solve() {
  std::cin >> g >> P >> n;
  for (i64 A, B; n; n--) {
    std::cin >> A >> B;
    i64 a = bsgs(g, A, P);
    std::cout << fast_pow(B, a, P) << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
