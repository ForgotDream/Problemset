/*
 * @file    P5074 Eat the Trees.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2024-01-06
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 13;
int n, m, a[N][N];

i64 f[1 << N], g[1 << N];

void solve() {
  std::cin >> n >> m;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) std::cin >> a[i][j];
  }

  int up = 1 << (m + 1);
  for (int i = 0; i < up; i++) g[i] = (i == 0);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      for (int st = 0; st < up; st++) {
        f[st] = j ? g[st] : (st & 1 ? 0 : g[st >> 1]);
      }
      if (!a[i][j]) {
        for (int st = 0; st < up; st++) {
          g[st] = (st >> j) & 3 ? 0 : f[st];
        }
      } else {
        for (int st = 0; st < up; st++) {
          g[st] = f[st ^ (3 << j)];
          if (((st >> j) & 1) != ((st >> (j + 1)) & 1)) {
            g[st] += f[st];
          }
        }
      }
    }
  }
  std::cout << g[0] << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  std::cin >> t;
  while (t--) solve();

  return 0;
}
