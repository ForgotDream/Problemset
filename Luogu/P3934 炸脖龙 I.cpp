/**
 * @file    P3934 炸脖龙 I.cpp
 * @author  ForgotDream
 * @brief   Nephren Tree
 * @date    2023-06-07
 */
#include <bits/stdc++.h>
#define int long long

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

struct BIT {
  int n;
  std::vector<int> tree;
  BIT(int _n) { n = _n, tree.resize(n); }
  void add(int u, int val) {
    if (u >= n) { return; }
    for (int i = u + 1; i <= n; i += (i & -i)) { tree[i - 1] += val; }
  }
  int query(int u) {
    int res = 0;
    for (int i = u + 1; i; i -= (i & -i)) { res += tree[i - 1]; }
    return res;
  }
};

std::pair<i64, bool> fastPow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  bool flg = false;
  if (base >= mod) { flg = true, base %= mod; }
  while (exp) {
    if (exp & 1) { 
      res *= base;
      if (res >= mod) { flg = true, res %= mod; } 
    }
    base *= base;
    if (base >= mod) { flg = true, base %= mod; }
    exp >>= 1;
  }
  return std::make_pair(res, flg);
}

std::vector<int> getPhi(int n) {
  std::vector<int> prime, phi(n + 1);
  std::vector<bool> isNotPrime(n + 1);
  phi[1] = 1;
  for (int i = 2; i <= n; i++) {
    if (!isNotPrime[i]) { prime.push_back(i), phi[i] = i - 1; }
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
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  FastIO::read(n, m);

  std::vector<int> a(n);
  BIT bit(n);
  for (int i = 0; i < n; i++) { 
    FastIO::read(a[i]);
    bit.add(i, a[i]), bit.add(i + 1, -a[i]);
  }

  auto phi = getPhi(2e7);
  std::function<std::pair<i64, bool>(int, int, int)> query = 
  [&](int l, int r, int mod) {
    i64 lval = bit.query(l);
    if (mod == 1) { return std::make_pair(0ll, true); }
    if (lval == 1) { return std::make_pair(1ll, false); }
    if (l == r) { 
      if (lval < mod) {
        return std::make_pair(lval, false);
      } else {
        return std::make_pair(lval % mod ,true);
      }
    }
    auto res = query(l + 1, r, phi[mod]);
    if (res.second) { res.first += phi[mod]; }
    return fastPow(lval, res.first, mod);
  };

  while (m--) {
    int opt, l, r, val;
    FastIO::read(opt, l, r, val);
    l--, r--;
    if (opt == 1) {
      bit.add(l, val), bit.add(r + 1, -val);
    } else {
      FastIO::print(query(l, r, val).first, '\n');
    }
  }

  return 0;
}