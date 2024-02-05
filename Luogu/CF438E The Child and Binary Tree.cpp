/*
 * @file    CF438E The Child and Binary Tree.cpp
 * @author  ForgotDream
 * @brief   Math + NTT
 * @date    2024-02-05
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;
using iter = std::vector<i64>::iterator;

constexpr int N = 1e6 + 50;
constexpr int mod = 998244353, g = 3;

i64 fast_pow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}

int r[N];

inline int expand(int len) {
  len = std::ceil(std::log(len) / std::log(2));
  return 1 << len;
}

void init(int len) {
  for (int i = 0; i < len; i++) r[i] = (r[i >> 1] >> 1) + (i & 1) * (len >> 1);
}

void perm(iter beg, iter end) {
  int len = end - beg;
  for (int i = 0; i < len; i++) if (i < r[i]) std::swap(beg[i], beg[r[i]]);
}

void ntt(iter beg, iter end, int opt) {
  perm(beg, end);
  int len = end - beg;
  for (int h = 2; h <= len; h <<= 1) {
    i64 delta = fast_pow(g, (mod - 1) / h, mod);
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

  std::vector<i64> g(2 * len), h(2 * len);
  g[0] = fast_pow(*beg, mod - 2, mod);

  for (int j = 2; j < len; j <<= 1) {
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

std::vector<i64> sqrt(iter beg, iter end) {
  int len = end - beg;
  
  std::vector<i64> g(2 * len), h(2 * len);
  g[0] = 1;

  for (int j = 2; j <= len; j <<= 1) {
    int k = j << 1;
    std::copy(beg, beg + j, h.begin());
    std::fill(h.begin() + j, h.begin() + k, 0);

    init(k);

    std::vector t(g.begin(), g.begin() + k);
    for (int i = 0; i < k; i++) t[i] = 2 * t[i] % mod;
    auto p = inv(t.begin(), t.end());

    ntt(g.begin(), g.begin() + k, 1);
    ntt(h.begin(), h.begin() + k, 1);
    ntt(p.begin(), p.begin() + k, 1);
    for (int i = 0; i < k; i++) {
      g[i] = (g[i] * g[i] % mod + h[i]) % mod;
      g[i] = g[i] * p[i] % mod;
    }
    ntt(g.begin(), g.begin() + k, -1);

    std::fill(g.begin() + j, g.begin() + k, 0);
  }

  return g;
}

int n, m;

void solve() {
  std::cin >> n >> m;

  std::vector<i64> g(m + 1);
  for (int i = 1, c; i <= n; i++) {
    std::cin >> c;
    if (c <= m) g[c] = mod - 4;
  }
  g[0] = 1;

  int len = expand(m + 1);
  init(len), g.resize(len);

  g = sqrt(g.begin(), g.end()), g[0]++;

  g = inv(g.begin(), g.end());
  for (int i = 1; i <= m; i++) std::cout << 2 * g[i] % mod << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
