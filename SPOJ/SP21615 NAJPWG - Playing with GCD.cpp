/**
 * @file    SP21615 NAJPWG - Playing with GCD.cpp
 * @author  ForgotDream
 * @brief   Euler Phi
 * @date    2023-05-10
 */
#include <bits/stdc++.h>
#define int long long

using i64 = long long;

std::vector<int> getPhi(int n) {
  std::vector<int> phi(n + 1), prime;
  std::vector<bool> isNotPrime(n + 1);

  phi[1] = 1;
  for (int i = 2; i <= n; i++) {
    if (!isNotPrime[i]) {
      phi[i] = i - 1;
      prime.push_back(i);
    }
    for (int j = 0; j < prime.size() && (i64) i * prime[j] <= n; j++) {
      isNotPrime[i * prime[j]] = true;
      if (!(i % prime[j])) {
        phi[i * prime[j]] = phi[i] * prime[j];
        break;
      } else {
        phi[i * prime[j]] = phi[i] * phi[prime[j]];
      }
    }
  }

  return phi;
}

std::vector<int> phi = getPhi(1e6);

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  for (int i = 1; i < phi.size(); i++) {
    phi[i] += phi[i - 1];
  }

  int t;
  std::cin >> t;

  for (int i = 0; i < t; i++) {
    int n;
    std::cin >> n;
    i64 ans = (i64) n * (n + 1) / 2 - phi[n];
    std::cout << "Case " << i + 1 << ": " << ans << "\n";
  }

  return 0;
}