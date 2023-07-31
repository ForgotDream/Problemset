/**
 * @file    CF1536E Omkar and Forest.cpp
 * @author  ForgotDream
 * @brief   Ad Hoc
 * @date    2023-07-28
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int mod = 1e9 + 7;

i64 fastPow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) {
      (res *= base) %= mod;
    }
    (base *= base) %= mod;
  }
  return res;
}

void solve() {
  int n, m;
  std::cin >> n >> m;
  int cnt = 0;
  for (int i = 0; i < n; i++) {
    std::string s;
    std::cin >> s;
    cnt += std::count(s.begin(), s.end(), '#');
  }
  std::cout << fastPow(2, cnt, mod) - (cnt == n * m) << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  std::cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}