/**
 * @file    CF295B Greg and Graph.cpp
 * @author  ForgotDream
 * @brief   最短路
 * @date    2023-08-20
 */
#include <iostream>
#include <cstring>

using i64 = long long;

constexpr int N = 550;
int n;
i64 x[N];
i64 dis[N][N], ans[N];
bool vis[N];

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      std::cin >> dis[i][j];
    }
  }
  for (int i = 1; i <= n; i++) std::cin >> x[i];

  for (int t = n; t >= 1; t--) {
    int k = x[t];
    vis[k] = true;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        dis[i][j] = std::min(dis[i][j], dis[i][k] + dis[k][j]);
      }
    }
    i64 cur = 0;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        if (!vis[i] || !vis[j]) continue;
        cur += dis[i][j];
      }
    }
    ans[t] = cur;
  }

  for (int i = 1; i <= n; i++) std::cout << ans[i] << " \n"[i == n];

  return 0;
}