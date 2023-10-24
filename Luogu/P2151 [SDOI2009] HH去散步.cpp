/**
 * @file    P2151 [SDOI2009] HH去散步.cpp
 * @author  ForgotDream
 * @brief   DP + Matrix Boost
 * @date    2023-08-07
 */
#include <bits/stdc++.h>
using i64 = long long;
constexpr int N = 55, mod = 45989;
int n, m, a, b, ans;
i64 t;
std::vector<std::pair<int, int>> adj[N];
template<int N = 121, typename T = int>
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
Matrix<> fastPow(Matrix<> init, Matrix<> base, int exp) {
  assert(base.r == base.c);
  Matrix res = init;
  for (; exp; exp >>= 1) {
    if (exp & 1) res = res * base;
    base = base * base;
  }
  return res;
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n >> m >> t >> a >> b;
  a++, b++;
  Matrix<>::mod = mod;
  Matrix<> f(2 * m, 2 * m), base(1, 2 * m);
  int cnt = 0;
  for (int i = 1, u, v; i <= m; i++) {
    std::cin >> u >> v;
    u++, v++;
    adj[u].emplace_back(v, cnt++), adj[v].emplace_back(u, cnt++);
  }
  for (int u = 1; u <= n; u++) {
    for (auto [v, i] : adj[u]) {
      for (auto [t, j] : adj[v]) {
        if (i == (j ^ 1)) continue;
        f.a[i + 1][j + 1]++;
      }
    }
  }
  for (auto [_, i] : adj[a]) base.a[1][i + 1]++;
  base = fastPow(base, f, t - 1);
  for (auto [_, i] : adj[b]) (ans += base.a[1][(i ^ 1) + 1]) %= mod;
  std::cout << ans << "\n";
  return 0;
}