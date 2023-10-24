/**
 * @file    P8865 种花.cpp
 * @author  ForgotDream
 * @brief   模拟
 * @date    2023-03-25
 */
#include <bits/stdc++.h>

using i64 = long long;
using f80 = long double;

void solve() {
  static const int MOD = 998244353;

  int n, m, c, f;
  std::cin >> n >> m >> c >> f;

  std::vector<std::vector<i64>> a(n, std::vector<i64>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      char c;
      std::cin >> c;
      a[i][j] = (c =='1');
    }
  }

  std::vector<std::vector<i64>> col(n, std::vector<i64>(m));
  auto row = col, down = col;
  for (int i = 0; i < n; i++) {
    for (int j = m - 1; ~j; j--) {
      if (a[i][j]) {
        col[i][j] = -1;
        continue;
      }
      if (j == m - 1) {
        col[i][j] = 0;
      } else {
        col[i][j] = col[i][j + 1] + 1;
      }
    }
  }
  for (int i = n - 1; ~i; i--) {
    for (int j = 0; j < m; j++) {
      if (a[i][j]) {
        row[i][j] = -1;
        continue;
      }
      if (i == n - 1) {
        row[i][j] = 0;
      } else {
        row[i][j] = row[i + 1][j] + 1;
      }
    }
  }
  for (int i = n - 1; ~i; i--) {
    for (int j = 0; j < m; j++) {
      if (a[i][j]) {
        down[i][j] = -1;
        continue;
      }
      if (i == n - 1 || a[i + 1][j]) {
        down[i][j] = i;
      } else {
        down[i][j] = down[i + 1][j];
      }
    }
  }

  auto sum1 = col, sum2 = col;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (i == 0 || a[i - 1][j]) {
        continue;
      }
      sum1[i][j] += sum1[i - 1][j];
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (i == 0 || a[i][j]) {
        continue;
      }
      (sum2[i][j] = sum2[i][j] * row[i][j] + sum2[i - 1][j]) %= MOD;
    }
  }

  i64 ans1 = 0, ans2 = 0;
  for (int i = 0; i < n - 2; i++) {
    for (int j = 0; j < m - 1; j++) {
      if (a[i][j] || a[i + 1][j] || !col[i][j]) {
        continue;
      }
      (ans1 += (sum1[down[i + 1][j]][j] - sum1[i + 1][j]) * col[i][j]) %= MOD;
    }
  }
  for (int i = 0; i < n - 3; i++) {
    for (int j = 0; j < m - 1; j++) {
      if (a[i][j] || a[i + 1][j] || !col[i][j]) {
        continue;
      }
      (ans2 += (sum2[down[i + 1][j]][j] - sum2[i + 1][j]) * col[i][j]) %= MOD;
    }
  }

  std::cout << (c * ans1) % MOD << " " << (f * ans2) % MOD << "\n";
  return;
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t, id;
  std::cin >> t >> id;

  while (t--) {
    solve();
  }

  return 0;
}