/*
 * @file    AT_agc024_e [AGC024E] Sequence Growing Hard.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2024-02-13
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 305;

int n, m, p;

i64 c[N][N], f[N][N], s[N][N];

void init(int _n) {
  for (int i = 0; i <= _n; i++) {
    c[i][0] = 1;
    for (int j = 1; j <= i; j++) {
      c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % p;
    }
  }
}

void solve() {
  std::cin >> n >> m >> p;

  init(n);

  for (int i = 1; i <= m + 1; i++) f[0][i] = 1;
  for (int i = m; i; i--) s[0][i] = s[0][i + 1] + f[0][i + 1];

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      for (int k = 0; k < i; k++) {
        f[i][j] += s[k][j] * f[i - k - 1][j] % p * c[i - 1][k] % p;
        f[i][j] %= p;
      }
    }
    for (int j = m; j; j--) s[i][j] = (s[i][j + 1] + f[i][j + 1]) % p;
  }

  std::cout << f[n][1] << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
