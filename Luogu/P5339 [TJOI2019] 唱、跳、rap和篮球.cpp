/*
 * @file    P5339 [TJOI2019] 唱、跳、rap和篮球.cpp
 * @author  ForgotDream
 * @brief   NTT + Math
 * @date    2024-02-01
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 2050, mod = 998244353;

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

using namespace POLYGON::NTT;

int n, a, b, c, d;

i64 fac[N], ifc[N];

void init(int _n) {
  fac[0] = ifc[0] = 1;
  for (int i = 1; i <= _n; i++) fac[i] = i * fac[i - 1] % mod;
  ifc[_n] = inv(fac[_n]);
  for (int i = _n - 1; i; i--) ifc[i] = (i + 1) * ifc[i + 1] % mod;
}

inline i64 C(i64 n, i64 m) {
  if (m > n) return 0;
  return fac[n] * ifc[m] % mod * ifc[n - m] % mod;
}

inline i64 calc(int n, int a, int b, int c, int d) {
  if (n < 0 || n > a + b + c + d) return 0;

  int lim = POLYGON::upper(a + b + c + d + 1);
  POLYGON::init(lim);
  std::vector<i64> A(lim), B(lim), C(lim), D(lim);

  for (int i = 0; i <= a; i++) A[i] = ifc[i];
  for (int i = 0; i <= b; i++) B[i] = ifc[i];
  for (int i = 0; i <= c; i++) C[i] = ifc[i];
  for (int i = 0; i <= d; i++) D[i] = ifc[i];
  ntt(A, 1), ntt(B, 1), ntt(C, 1), ntt(D, 1);
  for (int i = 0; i < lim; i++) A[i] = A[i] * B[i] % mod * C[i] % mod * D[i] % mod;
  ntt(A, -1);

  return fac[n] * A[n] % mod;
}

void solve() {
  std::cin >> n >> a >> b >> c >> d;
  init(n);
  int min = std::min({a, b, c, d});

  i64 ans = 0;
  for (int i = 0; i <= std::min(n / 4, min); i++) {
    i64 cur = C(n - 3 * i, i) * calc(n - 4 * i, a - i, b - i, c - i, d - i) % mod;
    if (i & 1) ans = (ans - cur + mod) % mod;
    else ans = (ans + cur) % mod;
  }
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
