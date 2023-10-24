/**
 * @file    P2579 [ZJOI2005] 沼泽鳄鱼.cpp
 * @author  ForgotDream
 * @brief   DP + Matrix Boost
 * @date    2023-08-07
 */
#include <bits/stdc++.h>
using i64 = long long;
constexpr int mod = 10000;
int n, m, s, t, k;
template<int N = 101, typename T = int>
struct Matrix {
  static inline int mod;
  int r, c;
  T a[N][N];
  Matrix() { r = c = 0, reset(); };
  Matrix(int _r) { r = c = _r, reset(); }
  Matrix(int _r, int _c) { r = _r, c = _c, reset(); }
  void reset() { std::memset(a, 0, sizeof(a)); }
  void resize(int _r, int _c) { r = _r, c = _c; }
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
  void print() {
    for (int i = 1; i <= r; i++)
      for (int j = 1; j <= c; j++) std::cout << a[i][j] << " \n"[j == c];
    std::cout << "\n";
  }
};
Matrix<> a[15];
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
  std::cin >> n >> m >> s >> t >> k;
  s++, t++;
  Matrix<> base(n, n);
  for (int i = 1, u, v; i <= m; i++) {
    std::cin >> u >> v;
    u++, v++;
    base.a[u][v]++, base.a[v][u]++;
  }
  for (int i = 1; i <= 12; i++) a[i] = base;
  a[0].resize(n, n), a[0].init();
  std::cin >> m;
  while (m--) {
    int cnt, tmp[5];
    std::cin >> cnt;
    for (int i = 0; i < cnt; i++) std::cin >> tmp[i], tmp[i]++;
    tmp[cnt] = tmp[0];
    for (int i = 1; i <= 12; i++) {
      for (int j = 1; j <= n; j++) {
        a[i].a[j][tmp[(i - 1) % cnt + 1]] = 0;
      }
    }
  }
  for (int i = 1; i <= 12; i++) a[0] = a[0] * a[i];
  a[0] = fastPow(a[0], k / 12);
  for (int i = 1; i <= k % 12; i++) a[0] = a[0] * a[i];
  std::cout << a[0].a[s][t] << "\n";
  return 0;
}