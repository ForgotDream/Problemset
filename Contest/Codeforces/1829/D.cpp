#include <bits/stdc++.h>

using i64 = long long;

std::vector<int> getPrime(int n) {
  std::vector<int> prime;
  std::vector<bool> isNotPrime(n + 5);

  for (int i = 2; i <= n; i++) {
    if (!isNotPrime[i]) {
      prime.push_back(i);
    }
    for (int j = 0; j < prime.size() && (i64) prime[j] * i <= n; i++) {
      isNotPrime[prime[j] * i] = true;
      if (!(i % prime[j])) {
        break;
      }
    }
  }

  return prime;
}

static std::vector<int> prime = getPrime(2e4);

std::vector<int> calc(int n, int &rst) {
  std::vector<int> factor(4e3 + 50);

  for (int i = 0; i < prime.size(); i++) {
    if (n % prime[i] == 0) {
      while (n % prime[i] == 0) {
        factor[prime[i]]++;
        n /= prime[i];
      }
    }
  }

  if (n != 1) {
    rst = n;
  }

  return factor;
} 

void solve() {
  int n, m;
  std::cin >> n >> m;

  if (n == m) {
    std::cout << "YES\n";
    return;
  }

  if (n % 3 != 0) {
    std::cout << "NO\n";
    return;
  }

  if (n < m) {
    std::cout << "NO\n";
    return;
  }

  int rst1 = 0, rst2 = 0;
  auto f1 = calc(n, rst1), f2 = calc(m, rst2);

  if (rst1 != rst2) {
    std::cout << "NO\n";
    return;
  }

  if (f2[2] < f1[2] || f1[3] <= f2[3]) {
    std::cout << "NO\n";
    return;
  }

  if (std::abs(f2[2] - f1[2]) > std::abs(f2[3] - f1[3])) {
    std::cout << "NO\n";
    return;
  }

  for (int i = 5; i < f1.size(); i++) {
    if (f1[i] != f2[i]) {
      std::cout << "NO\n";
      return;
    }
  }

  std::cout << "YES\n";

  return;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int t;
  std::cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}