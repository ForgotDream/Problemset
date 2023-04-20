/**
 * @file    P1217 回文质数 Prime Palindromes.cpp
 * @author  ForgotDream
 * @brief   枚举
 * @date    2023-03-20
 */
#include <bits/stdc++.h>

using i64 = long long;
using f80 = long double;

bool len(int num) {
  return !((1000 <= num && num <= 9999) || (100000 <= num && num <= 999999));
}

bool isPalin(int num) {
  if (num == 0) {
    return true;
  }
  std::vector<int> a;
  while (num) {
    a.push_back(num % 10);
    num /= 10;
  }
  for (int i = 0; i < a.size(); i++) {
    if (a[i] != a[a.size() - i - 1]) {
      return false;
    }
  }
  return true;
}

std::vector<bool> getPrime(int n) {
	std::vector<int> prime(n + 1);
  std::vector<bool> isNotPrime(n + 1);
  int cnt = 0;
  for (int i = 2; i <= n; i++) {
		if (!isNotPrime[i]) prime[++cnt] = i;
		for (int j = 1; j <= cnt && (i64) i * prime[j] <= n; j++) {
			isNotPrime[i * prime[j]] = true;
			if (!(i % prime[j])) break;
		}
	}
  return isNotPrime;
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int a, b;
  std::cin >> a >> b;

  if (a == 2) {
    std::cout << 2 << "\n";
  }

  if (a % 2 == 0) {
    a += 1;
  }

  b = std::min(b, 9999999);

  auto v = getPrime(b);

  for (int i = a; i <= b; i += 2) {
    if (len(i) && isPalin(i) && !v[i]) {
      std::cout << i << "\n";
      // printf("%d\n", i);
    }
  }

  return 0;
}