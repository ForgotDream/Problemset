/*
 * @file    P4726 【模板】多项式指数函数（多项式 exp）.cpp
 * @author  ForgotDream
 * @brief   Math + NTT
 * @date    2024-02-05
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;
using iter = std::vector<i64>::iterator;

constexpr int N = 4e5 + 50;
constexpr int mod = 998244353, g0 = 3;

inline i64 fast_pow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}

inline i64 inv(i64 u) { return fast_pow(u, mod - 2, mod); }

int r[N];

inline int expand(int len) {
  len = std::ceil(std::log(len) / std::log(2));
  return 1 << len;
}

void init(int len) {
  for (int i = 0; i < len; i++) r[i] = (r[i >> 1] >> 1) + (i & 1) * (len >> 1);
}

inline void perm(iter beg, iter end) {
  int len = end - beg;
  for (int i = 0; i < len; i++) if (i < r[i]) std::swap(beg[i], beg[r[i]]);
}

void ntt(iter beg, iter end, int opt) {
  perm(beg, end);
  int len = end - beg;
  for (int h = 2; h <= len; h <<= 1) {
    int delta = fast_pow(g0, (mod - 1) / h, mod);
    for (auto j = beg; j < end; j += h) {
      int w = 1;
      for (auto k = j; k < j + (h >> 1); k++) {
        i64 p = k[0], q = w * k[h >> 1] % mod;
        k[0] = (p + q) % mod;
        k[h >> 1] = (p - q + mod) % mod;
        w = 1ll * w * delta % mod;
      }
    }
  }
  if (opt == -1) {
    std::reverse(beg + 1, end);
    i64 inv = fast_pow(len, mod - 2, mod);
    for (int i = 0; i < len; i++) beg[i] = beg[i] * inv % mod;
  }
}

std::vector<i64> inv(iter beg, iter end) {
  int len = end - beg;

  std::vector<i64> g(len << 1), h(len << 1);
  g[0] = fast_pow(*beg, mod - 2, mod);

  for (int j = 2; j <= len; j <<= 1) {
    int k = j << 1;
    std::copy(beg, beg + j, h.begin());
    std::fill(h.begin() + j, h.begin() + k, 0);

    init(k);
    ntt(g.begin(), g.begin() + k, 1);
    ntt(h.begin(), h.begin() + k, 1);
    for (int i = 0; i < k; i++) {
      g[i] = g[i] * (2 - g[i] * h[i] % mod + mod) % mod;
    }
    ntt(g.begin(), g.begin() + k, -1);

    std::fill(g.begin() + j, g.begin() + k, 0);
  }

  return g;
}

std::vector<i64> derivative(iter beg, iter end) {
  int len = end - beg;
  std::vector<i64> g(len);
  for (int i = 1; i < len; i++) g[i - 1] = i * beg[i] % mod;
  return g;
}

std::vector<i64> integrate(iter beg, iter end) {
  int len = end - beg;
  std::vector<i64> g(len);
  for (int i = len - 1; i; i--) g[i] = beg[i - 1] * inv(i) % mod;
  return g;
}

std::vector<i64> ln(iter beg, iter end) {
  int len = end - beg, re = len << 1;

  auto d = derivative(beg, end), g = inv(beg, end);
  d.resize(re), g.resize(re);

  init(re);
  ntt(g.begin(), g.begin() + re, 1);
  ntt(d.begin(), d.begin() + re, 1);
  for (int i = 0; i < re; i++) d[i] = d[i] * g[i] % mod;
  ntt(d.begin(), d.begin() + re, -1);
  
  return integrate(d.begin(), d.begin() + len);
}

std::vector<i64> exp(iter beg, iter end) {
  int len = end - beg;

  std::vector<i64> g(len << 1), h(len << 1);
  g[0] = 1;

  for (int j = 2; j <= len; j <<= 1) {
    int k = j << 1;
    std::copy(beg, beg + j, h.begin());
    std::fill(h.begin() + j, h.begin() + k, 0);

    auto l = ln(g.begin(), g.begin() + j);
    for (int i = 0; i < j; i++) l[i] = (h[i] - l[i] + mod) % mod;
    l[0] = (l[0] + 1) % mod, l.resize(k);

    ntt(g.begin(), g.begin() + k, 1);
    ntt(l.begin(), l.begin() + k, 1);
    for (int i = 0; i < k; i++) g[i] = g[i] * l[i] % mod;
    ntt(g.begin(), g.begin() + k, -1);

    std::fill(g.begin() + j, g.begin() + k, 0);
  }

  return g;
}

int n;

void solve() {
  std::cin >> n;

  std::vector<i64> f(n);
  for (auto &i : f) std::cin >> i;

  int len = expand(n);
  init(len), f.resize(len);

  auto l = exp(f.begin(), f.end());
  for (int i = 0; i < n; i++) std::cout << l[i] << " \n"[i == n - 1];
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
