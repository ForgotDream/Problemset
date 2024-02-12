/*
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2024-02-12
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 305;

int n, m, p;

i64 c[N][N], f[N][N];

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

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      for (int k = 0; k < j; k++) {
        f[i][j] += f[k][j - 1] * f[]
      }
    }
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
