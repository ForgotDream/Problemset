/**
 * @file    P1069 细胞分裂.cpp
 * @author  ForgotDream
 * @brief   Factorize
 * @date    2023-06-07
 */
#include <bits/stdc++.h>

using i64 = long long;

std::vector<int> getPrime(int n) {
  std::vector<int> prime;
  std::vector<bool> isNotPrime(n + 1);
  for (int i = 2; i <= n; i++) {
    if (!isNotPrime[i]) { prime.push_back(i); }
    for (auto j : prime) {
      if (i * j > n) { break; }
      isNotPrime[i * j] = true;
      if (i % j == 0) { break; }
    }
  }
  return prime;
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m1, m2;
  std::cin >> n >> m1 >> m2;

  std::vector<int> a(n);
  for (int i = 0; i < n; i++) { std::cin >> a[i]; }

  auto prime = getPrime(std::ceil(std::sqrt(m1 + 0.5)));
  std::vector<std::pair<int, int>> factor;
  for (auto j : prime) {
    if (m1 % j == 0) {
      factor.emplace_back(j, 0);
      while (m1 % j == 0) {
        factor[factor.size() - 1].second++;
        m1 /= j;
      }
    }
  }
  if (m1 != 1) { factor.emplace_back(m1, 1); }

  int ans = INT_MAX;
  for (int i = 0; i < n; i++) {
    bool flg = true;
    int cnt = 0, cur = 0;
    for (auto j : factor) {
      if (a[i] % j.first != 0) {
        flg = false;
        break;
      }
      while (a[i] % j.first == 0) { cnt++, a[i] /= j.first; }
      cur = std::max(cur, int(std::ceil(1. * j.second * m2 / cnt)));
    }
    if (!flg) { continue; }
    ans = std::min(ans, cur);
  }

  if (ans == INT_MAX) {
    std::cout << -1 << "\n";
  } else {
    std::cout << ans << "\n";
  }

  return 0;
}