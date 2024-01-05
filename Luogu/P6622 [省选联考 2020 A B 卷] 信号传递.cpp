/*
 * @file    P6622 [省选联考 2020 A/B 卷] 信号传递.cpp  
 * @author  ForgotDream
 * @brief   DP on Subset
 * @date    2024-01-05
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int M = 23, LIM = 1 << M;
int n, m, k;

int f[LIM], g[M][M], w[M][M], c[M][M];

void solve() {
  std::cin >> n >> m >> k;
  
  int p = -1;
  for (int i = 1, u; i <= n; i++) {
    std::cin >> u, u--;
    if (p != -1) g[p][u]++;
    p = u;
  }

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
      if (i == j) continue;
      w[0][i] += g[j][i] * k - g[i][j];
      c[i][j] = g[i][j] * (1 + k) + g[j][i] * (1 - k);
    }
  }

  memset(f, 0x3f, sizeof(f)), f[0] = 0;
  
  int mask = (1 << m) - 1;
  for (int i = 0; i < mask; i++) {
    int u = std::__lg(i & -i), cnt = __builtin_popcount(i);
    if (cnt) {
      for (int j = 0; j < m; j++) w[cnt][j] = w[cnt - 1][j] + c[j][u];
    }
    for (int x = mask ^ i, y = x & -x; y; x ^= y, y = x & -x) {
      u = f[i] + w[cnt][std::__lg(y)] * (cnt + 1); 
      f[i | y] = std::min(f[i | y], u);
    }
  }
  std::cout << f[mask] << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
