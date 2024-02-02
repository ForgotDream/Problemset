/*
 * @file    P4238 【模板】多项式乘法逆.cpp
 * @author  ForgotDream
 * @brief   NTT + Newton's Method
 * @date    2024-02-02
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 4e5 + 50;
constexpr int mod = 998244353, g = 3;

int r[N];

void init(int len) {
  for (int i = 0; i < len; i++) r[i] = (r[i >> 1] >> 1) + (i & 1) * (len >> 1);
}

void perm(std::vector<i64>::iterator f, int len) {
  for (int i = 0; i < len; i++) if (i < r[i]) std::swap(f[i], f[r[i]]);
}

int expand(int len) {
  len = std::ceil(std::log(len) / std::log(2));
  return 1 << len;
}

inline i64 fast_pow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}

void ntt(std::vector<i64>::iterator f, int len, int opt) {
  perm(f, len);
  for (int h = 2; h <= len; h <<= 1) {
    int delta = fast_pow(g, (mod - 1) / h, mod);
    for (int j = 0; j < len; j += h) {
      int w = 1;
      for (int k = j; k < j + (h >> 1); k++) {
        i64 p = f[k], q = w * f[k + (h >> 1)] % mod;
        f[k] = (p + q) % mod;
        f[k + (h >> 1)] = (p - q + mod) % mod;
        w = 1ll * w * delta % mod;
      }
    }
  }
  if (opt == -1) {
    std::reverse(f + 1, f + len);
    i64 inv = fast_pow(len, mod - 2, mod);
    for (int i = 0; i < len; i++) f[i] = f[i] * inv % mod;
  }
}

int n;

std::vector<i64> inv(std::vector<i64> &f) {
  int len = f.size();

  std::vector<i64> g(2 * len), h(2 * len);
  g[0] = fast_pow(f[0], mod - 2, mod);

  for (int j = 2; j <= len; j <<= 1) {
    int k = j << 1;
    std::copy(f.begin(), f.begin() + j, h.begin());
    std::fill(h.begin() + j, h.begin() + k, 0);

    init(k);
    ntt(g.begin(), k, 1), ntt(h.begin(), k, 1);
    for (int i = 0; i < k; i++) {
      g[i] = g[i] * (2 - g[i] * h[i] % mod + mod) % mod;
    }
    ntt(g.begin(), k, -1);

    std::fill(g.begin() + j, g.begin() + k, 0);
  }

  return g;
}

void solve() {
  std::cin >> n;

  std::vector<i64> f(n);
  for (auto &i : f) std::cin >> i;

  int len = expand(n);
  f.resize(len);

  auto g = inv(f);
  for (int i = 0; i < n; i++) std::cout << g[i] << " \n"[i == n - 1];
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
