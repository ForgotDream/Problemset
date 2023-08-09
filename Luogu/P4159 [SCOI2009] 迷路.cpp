/**
 * @file    P4159 [SCOI2009] 迷路.cpp
 * @author  ForgotDream
 * @brief   DP + Matrix Boost
 * @date    2023-08-07
 */
#include <bits/stdc++.h>
using i64 = long long;
constexpr int mod = 2009;
int n, t, ans;
template<int N = 101, typename T = int>
struct Matrix {
  static inline int mod;
  int r, c;
  T a[N][N];
  Matrix() { r = c = 0, reset(); };
  Matrix(int _r) { r = c = _r, reset(); }
  Matrix(int _r, int _c) { r = _r, c = _c, reset(); }
  void reset() { std::memset(a, 0, sizeof(a)); }
  void init() {
    assert(r == c);
    for (int i = 1; i <= n; i++) a[i][i] = 1;
  }
  Matrix operator*(const Matrix &rhs) const {
    assert(c == rhs.r);
    Matrix res(r, rhs.c);
    for (int i = 1; i <= r; i++)
      for (int j = 1; j <= rhs.c; j++)
        for (int k = 1; k <= c; k++)
          (res.a[i][j] += (1ll * a[i][k] * rhs.a[k][j]) % mod) %= mod;
    return res;
  }
};
Matrix<> fastPow(Matrix<> base, int exp) {
  assert(base.r == base.c);
  Matrix res(base.r, base.c);
  res.init();
  for (; exp; exp >>= 1) {
    if (exp & 1) res = res * base;
    base = base * base;
  }
  return res;
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  Matrix<>::mod = mod;
  std::cin >> n >> t;
  Matrix<> base(9 * n, 9 * n);
  auto calc = [&](int u, int i) { return u + i * n; };
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= 8; j++) base.a[calc(i, j)][calc(i, j - 1)] = 1;
    for (int j = 1; j <= n; j++) {
      char a;
      std::cin >> a;
      if (a == '0') continue;
      base.a[i][calc(j, a - '0' - 1)] = 1;
    }
  }
  base = fastPow(base, t);
  std::cout << base.a[1][n] << "\n";
  return 0;
}