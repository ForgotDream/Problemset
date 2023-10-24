#include <bits/stdc++.h>

using i64 = long long;
using i128 = __int128;

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

  i64 a, m, x;
  std::cin >> a >> x >> m;

  // m = 1000000000;

  i64 powNum = 0;
  int block = std::sqrt(x);
  for (int i = 0; i < block; i++) {
    (powNum += fastPow(a, i, m)) %= m;
  }

  // std::cerr << powNum << " " << block << "\n";

  i64 ans = 0;
  for (int i = 1; i <= block; i++) {
    // std::cerr << i << " " << ((i64) (i - 1) * block) << "\n";
    (ans += fastPow(a, ((i64) (i - 1) * block), m) * i128(powNum)) %= m;
  }

  if ((i64) block * block != x) {
    for (i64 i = (i64) block * block; i < x; i++) {
      (ans += fastPow(a, i, m)) %= m;
    }
  }

  std::cout << ans << "\n";

  return 0;
}