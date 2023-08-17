#include <bits/stdc++.h>
#include <iostream>

using i64 = long long;

i64 slowMul(i64 a, i64 b, i64 mod) {
  i64 res = 0;
  while (b) {
    if (b & 1) {
      (res += a) %= mod;
    }
    (a += a) %= mod;
    b >>= 1;
  }
  return res;
}

i64 fastPow(i64 base, i64 pow, i64 mod) {
  i64 res = 1;
  while (pow) {
    if (pow & 1) {
      (res = slowMul(res, base, mod)) %= mod;
    }
    (base = slowMul(base, base, mod)) %= mod;
    pow >>= 1;
  }
  return res;
}

int main() {
  freopen("castle.in", "r", stdin);
  freopen("castle.out", "w", stdout);
  
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  
  static const int MOD = 1e9 + 7;
  
  i64 n;
  int k;
  std::cin >> n >> k;
  
  std::cout << slowMul(fastPow(k, k - 1, MOD), fastPow(n - k, n - k, MOD), MOD) << "\n";
  
  return 0;
}
