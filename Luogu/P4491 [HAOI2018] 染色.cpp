/*
 * @file    P4491 [HAOI2018] 染色.cpp
 * @author  ForgotDream
 * @brief   NTT + Binomial Inversion
 * @date    2024-01-31
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 1e7 + 50;
constexpr i64 mod = 1004535809;

inline i64 fast_pow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}
inline i64 inv(i64 u) { return fast_pow(u, mod - 2, mod); }

namespace POLYGON {

int r[N];

void init(int len) {
  for (int i = 0; i < len; i++) r[i] = (r[i >> 1] >> 1) + (i & 1) * (len >> 1);
}

inline int upper(int _n) {
  int l = std::ceil(std::log(_n) / std::log(2));
  l = 1 << l;
  return l;
}

namespace NTT {

constexpr int g = 3;

template <typename T>
void perm(std::vector<T> &f) {
  int len = f.size();
  for (int i = 0; i < len; i++) if (i < r[i]) std::swap(f[i], f[r[i]]);
}

template <typename T>
void ntt(std::vector<T> &f, int opt) {
  perm(f);
  int len = f.size();
  for (int h = 2; h <= len; h <<= 1) {
    int delta = fast_pow(g, (mod - 1) / h, mod);
    for (int j = 0; j < len; j += h) {
      int w = 1;
      for (int k = j; k < j + (h >> 1); k++) {
        auto cur = f[k];
        auto t = 1ll * w * f[k + (h >> 1)] % mod;
        f[k] = (cur + t) % mod;
        f[k + (h >> 1)] = (cur - t + mod) % mod;
        w = 1ll * w * delta % mod;
      }
    }
  }
  if (opt == -1) {
    std::reverse(f.begin() + 1, f.end());
    int inv = fast_pow(len, mod - 2, mod);
    for (int i = 0; i < len; i++) f[i] = 1ll * f[i] * inv % mod;
  }
}

}  // namespace NTT

}  // namespace POLYGON

int n, m, s, w[N];

i64 fac[N], ifc[N], lim;

void init(int _n) {
  fac[0] = ifc[0] = 1;
  for (int i = 1; i <= _n; i++) fac[i] = i * fac[i - 1] % mod;
  ifc[_n] = fast_pow(fac[_n], mod - 2, mod);
  for (int i = _n - 1; i; i--) ifc[i] = (i + 1) * ifc[i + 1] % mod;
}

inline i64 C(i64 n, i64 m) {
  return fac[n] * ifc[m] % mod * ifc[n - m] % mod;
}

inline i64 f(i64 k) {
  return C(m, k) * fac[n] % mod * fast_pow(ifc[s], k, mod) % mod * 
         ifc[n - s * k] % mod * fast_pow(m - k, n - s * k, mod) % mod;
}

void solve() {
  std::cin >> n >> m >> s, lim = std::min(m, n / s);
  for (int i = 0; i <= m; i++) std::cin >> w[i];

  init(std::max(n, m));

  std::vector<i64> A(lim + 1), B(lim + 1);
  for (int i = 0; i <= lim; i++) {
    A[i] = fac[i] * f(i) % mod;
    B[i] = (i & 1) ? mod - ifc[i] : ifc[i];
  }
  std::reverse(A.begin(), A.end());

  int expand = POLYGON::upper(2 * lim + 1);
  A.resize(expand), B.resize(expand);
  POLYGON::init(expand);

  POLYGON::NTT::ntt(A, 1), POLYGON::NTT::ntt(B, 1);
  for (int i = 0; i < expand; i++) A[i] = A[i] * B[i] % mod;
  POLYGON::NTT::ntt(A, -1);

  std::reverse(A.begin(), A.begin() + lim + 1);
  i64 ans = 0;
  for (int i = 0; i <= lim; i++) (ans += A[i] * ifc[i] % mod * w[i] % mod) %= mod;
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
