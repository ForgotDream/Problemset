/**
 * @file    P5136 sequence.cpp
 * @author  ForgotDream
 * @brief   Matrix + Fibonacci
 * @date    2023-05-05
 */
#include <bits/stdc++.h>

using i64 = long long;
using i64u = unsigned long long;
using f80 = long double;

constexpr int MOD = 998244353;

struct mat {
  int row, col;
  int arr[3][3];

  mat() { memset(arr, 0, sizeof(arr)); }
  mat(int x, int y) {
    row = x, col = y;
    memset(arr, 0, sizeof(arr));
  }

  void operator= (const mat& b) {
    for (int i = 1; i <= row; i++)
      for (int j = 1; j <= col; j++)
        arr[i][j] = b.arr[i][j];
    return;
  }

  mat operator* (const mat& b) const {
    mat res(row, b.col);
    for (int i = 1; i <= row; i++)
      for (int j = 1; j <= b.col; j++)
        for (int k = 1; k <= col; k++)
          res.arr[i][j] = (res.arr[i][j] + (i64) arr[i][k] * (i64) b.arr[k][j]) % MOD;
    return res;
  }
};

void solve() {
  i64 n;
  std::cin >> n;

  if (n == 0) {
    std::cout << 1 << "\n";
    return;
  } else if (n == 1) {
    std::cout << 2 << "\n";
    return;
  }

  int rst = n & 1;
  mat base(2, 2), res(2, 2);
  
  base.arr[1][1] = 1, base.arr[1][2] = 1;
  base.arr[2][1] = 1, base.arr[2][2] = 0;

  res.arr[1][1] = 3, res.arr[1][2] = 1;
  res.arr[2][1] = 0, res.arr[2][2] = 0;
  
  n -= 2;

  while (n) {
    if (n & 1) {
      res = res * base;
    }
    base = base * base;
    n >>= 1;
  }

  std::cout << (res.arr[1][1] + rst) % MOD << "\n";

  return;
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  std::cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}