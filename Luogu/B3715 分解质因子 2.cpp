/**
 * @file    B3715 分解质因子 2.cpp
 * @author  ForgotDream
 * @brief   Math
 * @date    2023-05-13
 */
#include <bits/stdc++.h>

using i64 = long long;

namespace FastIO{
  char buf[1 << 23], *p1 = buf, *p2 = buf;
  inline char gc() {
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 23, stdin), p1 == p2) ? EOF : *p1++;
  }

  template<typename T>
  inline void read(T& x) {
    x = 0;
    T f = 1;
    char c = gc();
    while (!isdigit(c)) {
      if (c == '-') f = -1;
      c = gc();
    }
    while (isdigit(c)) x = x * 10 + c - '0', c = gc();
    x *= f;
    return;
  }

  template<typename T, typename ... args>
  inline void read(T& x, args& ... tmp) {
    read(x);
    read(tmp...);
    return;
  }

  template<typename T>
  inline void print(T x) {
    if (x < 0) putchar('-'), x = -x;
    if (x / 10) print(x / 10);
    putchar(x % 10 + '0');
    return;
  }

  template<typename T>
  inline void print(T x, char c) {
    print(x), putchar(c);
    return;
  }
}

std::vector<int> getPrime(int n) {
  std::vector<int> prime;
  std::vector<bool> isNotPrime(n + 1);
  for (int i = 2; i <= n; i++) {
    if (!isNotPrime[i]) {
      prime.push_back(i);
    }
    for (int j = 0; j < prime.size() && 1ll * prime[j] * i <= n; j++) {
      isNotPrime[i * prime[j]] = true;
      if (!(i % prime[j])) {
        break;
      }
    }
  }
  return prime;
}

signed main() {
  // std::ios::sync_with_stdio(false);
  // std::cin.tie(nullptr);

  auto prime = getPrime(1e6);

  int t;
  FastIO::read(t);

  while (t--) {
    i64 n;
    FastIO::read(n);
    for (int i = 0; i < prime.size() && prime[i] * prime[i] <= n; i++) {
      while (n % prime[i] == 0) {
        FastIO::print(prime[i], ' ');
        n /= prime[i];
      }
    }
    if (n != 1) {
      FastIO::print(n);
    }
    putchar('\n');
  }

  return 0;
}