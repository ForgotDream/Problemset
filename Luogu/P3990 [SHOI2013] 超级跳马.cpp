/**
 * @file    P3990 [SHOI2013] 超级跳马.cpp
 * @author  ForgotDream
 * @brief   Matrix + DP
 * @date    2023-11-22
 */
#include <bits/stdc++.h>

using i64 = int64_t;

constexpr int N = 105, mod = 30011;
int n, m;
struct Mat {
  int a[N][N];
  Mat() { memset(a, 0, sizeof(a)); }
  int *operator[](size_t idx) { return a[idx]; }
  const int *operator[](size_t idx) const { return a[idx]; }
  friend Mat operator*(const Mat &lhs, const Mat &rhs) {
    Mat res;
    for (int i = 0; i < 2 * n; i++) {
      for (int j = 0; j < 2 * n; j++) {
        for (int k = 0; k < 2 * n; k++) {
          res[i][j] = (res[i][j] + lhs[i][k] * rhs[k][j] % mod) % mod;
        }
      }
    }
    return res;
  }
  friend Mat operator-(const Mat &lhs, const Mat &rhs) {
    Mat res;
    for (int i = 0; i < 2 * n; i++) {
      for (int j = 0; j < 2 * n; j++) res[i][j] = (lhs[i][j] - rhs[i][j] + mod) % mod;
    }
    return res;
  }
  void norm() {
    for (int i = 0; i < 2 * n; i++) a[i][i] = 1;
  }
} F, ans;
Mat fastPow(Mat base, int exp) {
  Mat res;
  res.norm();
  for (; exp; exp >>= 1) {
    if (exp & 1) res = res * base;
    base = base * base;
  }
  return res;
}
void solve() {
  std::cin >> n >> m;
  for (int i = 0; i < n; i++) {
    if (i != 0) F[i][i - 1] = 1;
    F[i][i] = F[i][i + n] = 1;
    if (i != n - 1) F[i][i + 1] = 1;
    F[i + n][i] = 1;
  }
  auto T = fastPow(F, m - 2);
  ans[0][0] = 1;
  std::cout << ((T * F)[n - 1][0] - T[2 * n - 1][0] + mod) % mod << "\n";
  // for (int i = 0; i < 2 * n; i++) std::cout << (F * ans)[i][0] << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
