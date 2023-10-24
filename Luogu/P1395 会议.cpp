/**
 * @file    P1395 会议.cpp
 * @author  ForgotDream
 * @brief   树的重心
 * @date    2023-05-09
 */
#include <bits/stdc++.h>

using i64 = long long;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int n;
  std::cin >> n;

  std::vector<std::vector<int>> g(n + 1);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    std::cin >> u >> v;
    g[u].push_back(v), g[v].push_back(u);
  }

  std::vector<int> siz(n + 1), maxsiz(n + 1);
  std::vector<int> ctr;
  std::function<void(int, int)> dfs1 = [&](int u, int frm) {
    siz[u] = 1, maxsiz[u] = 0;
    for (auto v : g[u]) {
      if (v == frm) {
        continue;
      }
      dfs1(v, u);
      siz[u] += siz[v];
      maxsiz[u] = std::max(maxsiz[u], siz[v]);
    }
    maxsiz[u] = std::max(maxsiz[u], n - siz[u]);
    if (maxsiz[u] <= n / 2) {
      ctr.push_back(u);
    }
    return;
  };

  dfs1(1, 0);

  std::sort(ctr.begin(), ctr.end());
  std::cout << ctr[0] << " ";

  std::vector<int> dis(n + 1);
  std::function<void(int, int)> dfs2 = [&](int u, int frm) {
    dis[u] = dis[frm] + 1;
    for (auto v : g[u]) {
      if (v == frm) {
        continue;
      }
      dfs2(v, u);
    }
    return;
  };

  dfs2(ctr[0], 0);

  int ans = 0;
  for (int i = 1; i <= n; i++) {
    ans += dis[i] - 1;
  }

  std::cout << ans << "\n";

  return 0;
}