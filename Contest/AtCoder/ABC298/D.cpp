#include <bits/stdc++.h>

using i64 = long long;

i64 fastPow(i64 base, i64 pow, i64 mod) {
  i64 res = 1;
  while (pow) {
    if (pow & 1) {
      (res *= base) %= mod;
    }
    (base *= base) %= mod;
    pow >>= 1;
  }
  return res;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  static const int MOD = 998244353;
  int q, pivot = 0;
  i64 cur = 1;
  std::string s = "1";
  std::cin >> q;

  while (q--) {
    int opt;
    std::cin >> opt;
    if (opt == 1) {
      char x;
      std::cin >> x;
      s += x;
      cur = (10 * cur % MOD + x - '0') % MOD;
    } else if (opt == 2) {
      (cur -= (s[pivot] - '0') * fastPow(10, s.length() - pivot - 1, MOD)) %= MOD;
      pivot++;
      (cur += MOD) %= MOD;
    } else {
      std::cout << cur << "\n";
    }
  }

  return 0;
}