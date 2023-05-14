/**
 * @file    B3716 分解质因子 3.cpp
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
  std::vector<int> prime, p(n + 1);
  std::vector<bool> isNotPrime(n + 1);
  for (int i = 2; i <= n; i++) {
    if (!isNotPrime[i]) {
      prime.push_back(i);
      p[i] = i;
    }
    for (int j = 0; j < prime.size() && 1ll * prime[j] * i <= n; j++) {
      isNotPrime[i * prime[j]] = true;
      p[i * prime[j]] = prime[j];
      if (!(i % prime[j])) {
        break;
      }
    }
  }
  return p;
}

signed main() {
  // std::ios::sync_with_stdio(false);
  // std::cin.tie(nullptr);

  auto prime = getPrime(1e8);

  int t;
  FastIO::read(t);

  while (t--) {
    int n, ans = 0;
    FastIO::read(n);
    while (n > 1) {
      ans ^= prime[n];
      n /= prime[n];
    }
    FastIO::print(ans, '\n');
  }

  return 0;
}