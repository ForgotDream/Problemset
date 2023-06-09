/**
 * @file    P4139 上帝与集合的正确用法.cpp
 * @author  ForgotDream
 * @brief   Extended Euler Theorem
 * @date    2023-06-07
 */
#include <bits/stdc++.h>

using i64 = long long;

std::vector<int> getPhi(int n) {
  std::vector<int> phi(n + 1), prime;
  std::vector<bool> isNotPrime(n + 1);
  phi[1] = 1;
  for (int i = 2; i <= n; i++) {
    if (!isNotPrime[i]) { phi[i] = i - 1, prime.push_back(i); }
    for (auto j : prime) {
      if (i * j > n) { break; }
      isNotPrime[i * j] = true;
      if (i % j == 0) { 
        phi[i * j] = phi[i] * j;
        break; 
      } else {
        phi[i * j] = phi[i] * phi[j];
      }
    }
  }
  return phi;
};

i64 fastPow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  while (exp) {
    if (exp & 1) { (res *= base) %= mod; }
    (base *= base) %= mod;
    exp >>= 1;
  }
  return res;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  std::cin >> t;

  auto phi = getPhi(1e7);
  i64 mod;
  std::function<i64(int)> solve = [&](int cur) { 
    if (cur == 1) { return 0ll; }
    return fastPow(2ll, solve(phi[cur]) + phi[cur], cur);
  };

  while (t--) {
    std::cin >> mod;
    std::cout << solve(mod) << "\n";
  }

  return 0;
}