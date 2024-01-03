/*
 * @file    P3216 [HNOI2011] 数学作业.cpp
 * @author  ForgotDream
 * @brief   Matrix + DP
 * @date    2024-01-03
 */
#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;

u64 n, m;

struct Mat {
  i64 a[3][3];
  i64 *operator[](size_t idx) { return a[idx]; }
  const i64 *operator[](size_t idx) const { return a[idx]; }
  Mat() { memset(a, 0, sizeof(a)); }
  static Mat eye() {
    Mat res;
    for (int i = 0; i < 3; i++) res[i][i] = 1;
    return res;
  }
  friend Mat operator*(const Mat &lhs, const Mat &rhs) {
    Mat res;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        for (int k = 0; k < 3; k++) {
          res[i][j] = (res[i][j] + lhs[i][k] * rhs[k][j] + m) % m;
        }
      }
    }
    return res;
  }
};

std::ostream &operator<<(std::ostream &os, const Mat &mat) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) os << mat[i][j] << " \n"[j == 2];
  }
  return os;
}

Mat fastPow(Mat base, i64 exp) {
  Mat res = Mat::eye();
  for (; exp; exp >>= 1) {
    if (exp & 1) res = res * base;
    base = base * base;
  }
  return res;
}

u64 pw10[20];

void solve() {
  std::cin >> n >> m, n++;

  pw10[0] = 1;
  for (int i = 1; i < 20; i++) pw10[i] = 10 * pw10[i - 1];

  Mat base, res;
  res[0][0] = 0, res[1][0] = 0, res[2][0] = 1;
  base[0][2] = 1, base[1][2] = 1, base[2][1] = -1, base[2][2] = 2;
  
  // std::cerr << base << "\n";
  // std::cerr << base * base << "\n";
  // std::cerr << fastPow(base, 2) << "\n";

  for (int i = 1; i <= std::ceil(1 + std::log10(n)); i++) {
    base[0][0] = pw10[i] % m;
    if (n < pw10[i]) {
      res = fastPow(base, n - pw10[i - 1]) * res;
      std::cout << res[0][0] << "\n";
      return;
    }
    res = fastPow(base, pw10[i] - pw10[i - 1]) * res;
    // std::cerr << base << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
