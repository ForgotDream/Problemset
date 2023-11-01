/**
 * @file    CF1662C European Trip.cpp
 * @author  ForgotDream
 * @brief   DP + Matrix 
 * @date    2023-11-01
 */
#include <cassert>
#include <cstring>
#include <iostream>
#include <vector>

using i64 = long long;

constexpr int N = 105, mod = 998244353;
int n, m, k;
std::vector<int> adj[N];
// 感觉，有点套路
template<i64 MOD = mod>
struct ModInt {
  i64 val;
  explicit operator i64() { return val; }
  ModInt(const i64 &v = 0) : val(v % MOD) {}
  ModInt<MOD> &operator+=(const ModInt<MOD> &rhs) {
    val = (val + rhs.val) % MOD;
    return *this;
  }
  ModInt<MOD> &operator-=(const ModInt<MOD> &rhs) {
    val = (val - rhs.val + MOD) % MOD;
    return *this;
  }
  ModInt<MOD> &operator*=(const ModInt<MOD> &rhs) {
    val = (val * rhs.val) % MOD;
    return *this;
  }
  ModInt<MOD> &operator++() { return *this += 1; }
  ModInt<MOD> &operator--() { return *this -= 1; }
  ModInt<MOD> operator++(int) {
    auto cur = *this;
    ++(*this);
    return cur;
  }
  ModInt<MOD> operator--(int) {
    auto cur = *this;
    --(*this);
    return cur;
  }
  friend ModInt<MOD> operator+(const ModInt<MOD> &lhs, const ModInt<MOD> &rhs) {
    return ModInt<MOD>((lhs.val + rhs.val) % MOD);
  }
  friend ModInt<MOD> operator-(const ModInt<MOD> &lhs, const ModInt<MOD> &rhs) {
    return ModInt<MOD>((lhs.val - rhs.val + MOD) % MOD);
  }
  friend ModInt<MOD> operator*(const ModInt<MOD> &lhs, const ModInt<MOD> &rhs) {
    return ModInt<MOD>((lhs.val * rhs.val) % MOD);
  }
};
template <typename T, size_t SIZ>
struct Matrix {
  size_t row, col;
  T a[SIZ][SIZ];
  bool i = true;
  Matrix() { init(); };
  Matrix(const size_t &r, const size_t &c) : row(r), col(c) { init(); }
  void init() { std::memset(a, 0, sizeof(a)); }
  T *operator[](const size_t &idx) { return a[idx]; }
  const T *operator[](const size_t &idx) const { return a[idx]; }
  friend Matrix<T, SIZ> operator+(const Matrix<T, SIZ> &lhs,
                                  const Matrix<T, SIZ> &rhs) {
    assert(lhs.col == rhs.col && lhs.row == rhs.row);
    Matrix<T, SIZ> res(lhs.row, lhs.col);
    for (size_t i = 0; i < res.row; i++) {
      for (size_t j = 0; j < res.col; j++) {
        res[i][j] = lhs[i][j] + rhs[i][j];
      }
    }
    return res;
  }
  friend Matrix<T, SIZ> operator*(const Matrix<T, SIZ> &lhs,
                                  const Matrix<T, SIZ> &rhs) {
    assert(lhs.col == rhs.row);
    Matrix<T, SIZ> res(lhs.row, rhs.col);
    std::vector vis(SIZ, std::vector<bool>(SIZ, false));
    for (size_t i = 0; i < res.row; i++) {
      for (size_t j = 0; j < res.col; j++) {
        for (size_t k = 0; k < lhs.col; k++) {
          if (!vis[i][j]) res[i][j] = lhs[i][k] * rhs[k][j], vis[i][j] = true;
          else res[i][j] = res[i][j] + lhs[i][k] * rhs[k][j];
        }
      }
    }
    return res;
  }
};
// 不知道咋给矩阵套矩阵赋单位矩阵，所以大概只能投机取巧一下（
template <typename T, size_t SIZ>
Matrix<T, SIZ> fastPow(Matrix<T, SIZ> base, unsigned int exp) {
  assert(exp > 0);
  exp--;
  auto res = base;
  for (; exp; exp >>= 1) {
    if (exp & 1) res = res * base;
    base = base * base;
  }
  return res;
}
void solve() {
  std::cin >> n >> m >> k;
  if (k <= 2) {
    std::cout << 0 << "\n";
    return;
  }
  Matrix<ModInt<mod>, N> ADJ(n, n), DEG(n, n), I(n, n), EMPTY(n, n);
  for (int i = 0; i < n; i++) I[i][i] = 1;
  DEG = I;
  for (int i = 1, u, v; i <= m; i++) {
    std::cin >> u >> v, u--, v--;
    ADJ[u][v] = ADJ[v][u] = 1;
    DEG[u][u]--, DEG[v][v]--;
  }
  k -= 2;
  auto F1 = ADJ * ADJ;
  for (int i = 0; i < n; i++) F1[i][i] = 0;
  Matrix<Matrix<ModInt<mod>, N>, 2> F(2, 2);
  F[0][0] = EMPTY, F[0][1] = DEG;
  F[1][0] = I, F[1][1] = ADJ;
  F = fastPow(F, k);
  // for (int i = 1; i < k; i++) F = F * F;
  auto ANS = F1 * F[1][1] + ADJ * F[0][1];
  ModInt<mod> ans = 0;
  for (int i = 0; i < n; i++) ans += ANS[i][i];
  std::cout << i64(ans) << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
