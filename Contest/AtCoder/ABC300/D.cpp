#include <bits/stdc++.h>

using i64 = long long;

std::vector<i64> getPrime(const int &n) {
  std::vector<i64> prime;
  std::vector<bool> isNotPrime(n + 1);

  for (int i = 2; i <= n; i++) {
    if (!isNotPrime[i]) {
      prime.push_back(i);
    }
    for (int j = 0; j < prime.size() && (i64) i * prime[j] <= n; j++) {
      isNotPrime[i * prime[j]] = true;
      if (!(i % prime[j])) {
        break;
      }
    }
  }

  return prime;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  i64 n;
  std::cin >> n;

  auto prime = getPrime(std::pow(n, 0.5) + 50);
  int primeCnt = prime.size();

  int ans = 0;
  for (int i = 0; i < primeCnt; i++) {
    for (int j = i + 2; j < primeCnt; j++) {
      if (prime[i] * prime[j] > std::sqrt(n / prime[i + 1])) {
        break;
      }
      i64 prod = prime[i] * prime[i] * prime[j] * prime[j];
      i64 rst = n / prod;
      if (rst <  prime[i + 1]) {
        continue;
      }
      i64 min = std::min(rst, prime[j - 1]);
      i64 tmp = *std::lower_bound(prime.begin(), prime.end(), min);
      int cur = std::lower_bound(prime.begin(), prime.end(), min) - prime.begin() - (i + (min != tmp));
      ans += cur;
    }
  }

  std::cout << ans << "\n";

  return 0;
}