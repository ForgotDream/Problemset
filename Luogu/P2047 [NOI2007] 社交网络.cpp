/**
 * @file    P2047 [NOI2007] 社交网络.cpp
 * @author  ForgotDream
 * @brief   Floyd
 * @date    2023-11-22
 */
#include <bits/stdc++.h>

using i64 = int64_t;
using pii = std::pair<int, int>;

constexpr int N = 105;
int n, m, dis[N][N];
i64 f[N][N];
void solve() {
  std::cin >> n >> m;
  memset(dis, 0x3f, sizeof(dis));
  for (int i = 1, u, v, w; i <= m; i++) {
    std::cin >> u >> v >> w;
    dis[u][v] = dis[v][u] = w;
    f[u][v] = f[v][u] = 1;
  }
  for (int k = 1; k <= n; k++) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        int d = dis[i][k] + dis[k][j];
        if (dis[i][j] > d) dis[i][j] = d, f[i][j] = f[i][k] * f[k][j];
        else if (dis[i][j] == d) f[i][j] += f[i][k] * f[k][j];
      }
    }
  }
  for (int k = 1; k <= n; k++) {
    double cur = 0;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        if (i == j || i == k || j == k) continue;
        if (dis[i][k] + dis[k][j] != dis[i][j]) continue;
        cur += 1. * (f[i][k] * f[k][j]) / f[i][j];
      }
    }
    std::cout << std::fixed << std::setprecision(3) << cur << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
