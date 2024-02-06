/*
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2024-02-06
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;
using poly = std::vector<i64>;
using iter = poly::iterator;

constexpr int N = 5e5 + 50;
constexpr int mod = 998244353, G = 3;

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

void init(int len) {
  for (int i = 0; i < len; i++) r[i] = (r[i >> 1] >> 1) + (i & 1) * (len >> 1);
}

inline int expand(int len) {
  len = std::ceil(std::log(len) / std::log(2));
  return 1 << len;
}

void perm(iter beg, iter end) {
  int len = end - beg;
  for (int i = 0; i < len; i++) if (i < r[i]) std::swap(beg[i], beg[r[i]]);
}

void ntt(iter beg, iter end, int opt) {
  int len = end - beg;
  perm(beg, end);
  for (int h = 2; h <= len; h <<= 1) {
    i64 delta = fast_pow(G, (mod - 1) / h, mod);
    for (auto j = beg; j < end; j += h) {
      i64 w = 1;
      for (auto k = j; k < j + (h >> 1); k++) {
        i64 p = k[0], q = w * k[h >> 1] % mod;
        k[0] = (p + q) % mod;
        k[h >> 1] = (p - q + mod) % mod;
        w = w * delta % mod;
      }
    }
  }
  if (opt == -1) {
    std::reverse(beg + 1, end);
    i64 inv = fast_pow(len, mod - 2, mod);
    for (int i = 0; i < len; i++) beg[i] = beg[i] * inv % mod;
  }
}

poly inv(iter beg, iter end) {
  int len = end - beg;

  poly g(len << 1), h(len << 1);
  g[0] = inv(*beg);

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

  g.resize(len);
  return g;
}

std::pair<poly, poly> div(iter nbeg, iter nend, iter dbeg, iter dend) {
  int n = nend - nbeg, m = dend - dbeg;

  int len = expand((n - m + 1) * 2);
  
  poly d(nbeg, nend), r(m);
  std::reverse(d.begin(), d.end());

  std::vector t(dbeg, dend);
  std::reverse(t.begin(), t.end());

  return {d, r};
}

void solve() {
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
