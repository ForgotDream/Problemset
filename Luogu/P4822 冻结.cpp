/**
 * @file    P4822 冻结.cpp
 * @author  ForgotDream
 * @brief   分层图
 * @date    2023-05-09
 */
#include <bits/stdc++.h>

using i64 = long long;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int n, m, k;
  std::cin >> n >> m >> k;

  std::vector g(n, std::vector<std::pair<int, int>>());
  for (int i = 0; i < m; i++) {
    int u, v, w;
    std::cin >> u >> v >> w;
    u--, v--;
    g[u].emplace_back(v, w);
    g[v].emplace_back(u, w);
  }
  
  std::vector dis(n, std::vector<int>(k + 1, 1e9));
  std::vector vis(n, std::vector<bool>(k + 1));
  std::priority_queue<
    std::tuple<int, int, int>,
    std::vector<std::tuple<int, int, int>>,
    std::greater<std::tuple<int, int, int>>
  > pq;
  pq.emplace(0, 0, 0);
  dis[0][0] = 0;
  while (!pq.empty()) {
    int u = std::get<1>(pq.top()), cnt = std::get<2>(pq.top());
    pq.pop();
    if (vis[u][cnt]) {
      continue;
    }
    vis[u][cnt] = true;
    for (auto i : g[u]) {
      int v = i.first, w = i.second;
      if (cnt < k && dis[v][cnt + 1] > dis[u][cnt] + w / 2) {
        dis[v][cnt + 1] = dis[u][cnt] + w / 2;
        pq.emplace(dis[v][cnt + 1], v, cnt + 1);
      }
      if (dis[v][cnt] > dis[u][cnt] + w) {
        dis[v][cnt] = dis[u][cnt] + w;
        pq.emplace(dis[v][cnt], v, cnt);
      }
    }
  }

  int ans = 1e9;
  for (int i = 0; i <= k; i++) {
    ans = std::min(ans, dis[n - 1][i]);
  }

  std::cout << ans << "\n";

  return 0;
}