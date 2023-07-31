/**
 * @file    CF266D BerDonalds.cpp
 * @author  ForgotDream
 * @brief   Shortest Path
 * @date    2023-07-28
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 250, M = 4e4 + 50;
int n, m;
struct Edge {
  int u, v, w;
} edges[M];
int dis[N][N], rnk[N][N], ans = 0x3f3f3f3f;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout << std::fixed << std::setprecision(12);

  std::memset(dis, 0x3f, sizeof(dis));

  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) dis[i][i] = 0;
  for (int i = 1; i <= m; i++) {
    auto &[u, v, w] = edges[i];
    std::cin >> u >> v >> w;
    dis[u][v] = dis[v][u] = std::min(dis[u][v], w);
  }

  for (int k = 1; k <= n; k++) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        dis[i][j] = std::min(dis[i][j], dis[i][k] + dis[k][j]);
      }
    }
  }
  
  for (int i = 1 ; i <= n; i++) {
    std::iota(rnk[i], rnk[i] + N, 0);
    std::sort(rnk[i] + 1, rnk[i] + n + 1, [&](int lhs, int rhs) {
      return dis[i][lhs] < dis[i][rhs];
    });
  }
  for (int i = 1; i <= n; i++) ans = std::min(ans, 2 * dis[i][rnk[i][n]]);
  for (int i = 1; i <= m; i++) {
    auto [u, v, w] = edges[i];
    int pivot = n;
    for (int j = n; j >= 1; j--) {
      if (dis[v][rnk[u][j]] > dis[v][rnk[u][pivot]]) {
        ans = std::min(ans, dis[u][rnk[u][j]] + dis[v][rnk[u][pivot]] + w);
        pivot = j;
      }
    }
  }

  std::cout << 1. * ans / 2 << "\n";

  return 0;
}