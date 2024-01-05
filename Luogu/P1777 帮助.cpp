/*
 * @file    P1777 帮助.cpp
 * @author  ForgotDream
 * @brief   DP on Subset
 * @date    2024-01-04
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 105, M = 8, d = 25;
int n, K, a[N];

int f[N][N][1 << M][M + 1];

inline void chkmin(int &u, const int &v) { u = u < v ? u : v; }
inline void chkmax(int &u, const int &v) { u = u > v ? u : v; }

void solve() {
  static int t = 0;
  std::cout << std::format("Case {}: ", ++t);

  memset(f, 0x3f, sizeof(f));

  int st = 0;
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i], a[i] -= d, st |= (1 << a[i]);
  }

  f[1][0][1 << a[1]][a[1]] = 1, f[1][1][0][8] = 0;

  for (int i = 1; i < n; i++) {
    for (int j = 0; j <= K; j++) {
      for (int k = 0; k < (1 << M); k++) {
        for (int l = 0; l <= M; l++) {
          if (f[i][j][k][l] == 0x3f3f3f3f) continue;
          chkmin(f[i + 1][j][k | (1 << a[i + 1])][a[i + 1]],
                 f[i][j][k][l] + (a[i + 1] != l));
          chkmin(f[i + 1][j + 1][k][l], f[i][j][k][l]);
        }
      }
    }
  }

  int ans = 0x3f3f3f3f;
  for (int i = 0; i <= K; i++) {
    for (int j = 0; j < (1 << M); j++) {
      for (int k = 0; k < M; k++) {
        if (f[n][i][j][k] == 0x3f3f3f3f) continue;
        chkmin(ans, f[n][i][j][k] + __builtin_popcount(st ^ j));
      }
    }
  }
  std::cout << ans << "\n\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  // int t = 1;
  // std::cin >> t;
  // while (t--) solve();
  
  while (std::cin >> n >> K && n && K) solve();

  return 0;
}
