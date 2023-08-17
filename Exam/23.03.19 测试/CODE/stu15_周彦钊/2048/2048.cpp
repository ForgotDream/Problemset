#include <bits/stdc++.h>
#include <vector>
#include <iostream>

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
  freopen("2048.in", "r", stdin);
  freopen("2048.out", "w", stdout);
  
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  
  static const int MOD = 998244353, M = 1 << 11;
  
  int n;
  std::cin >> n;
  
  std::vector<int> a;
  int rst = 0;
  for (int i = 0; i < n; i++) {
    int cur;
    std::cin >> cur;
    if (__builtin_popcount(cur) == 1) {
      a.push_back(cur);
    } else {
      rst++;
    }
  }
  
  if (!a.size()) {
    std::cout << 0 << "\n";
    return 0;
  }
  
  std::vector<int> f(M + 1);
  f[0] = 1;
  for (int i = 0; i < a.size(); i++) {
    for (int j = M; j >= a[i]; j--) {
      (f[j] += f[j - a[i]]) %= MOD;
    }
  }
  for (int i = 1; i <= M; i++) {
    (f[i] += f[i - 1]) %= MOD;
  }
  
  i64 ans = (fastPow(2, a.size(), MOD) - f[M - 1] + MOD) % MOD;
  (ans *= fastPow(2, rst, MOD)) %= MOD;
  std::cout << ans << "\n";
  
  // std::cerr << (double) std::clock() / CLOCKS_PER_SEC << "\n";
  
  return 0;
}
