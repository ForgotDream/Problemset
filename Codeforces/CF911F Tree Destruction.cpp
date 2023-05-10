/**
 * @file    CF911F Tree Destruction.cpp
 * @author  ForgotDream
 * @brief   Tree Diameter
 * @date    2023-05-10
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

  std::vector<int> dis(n + 1), nxt(n + 1);
  std::function<void(int, int)> dfs = [&](int u, int frm) {
    dis[u] = dis[frm] + 1;
    nxt[u] = frm;
    for (auto v : g[u]) {
      if (v == frm) {
        continue;
      }
      dfs(v, u);
    }
  };

  dfs(1, 0);
  int L = 1, R = 1;
  for (int i = 1; i <= n; i++) {
    if (dis[L] < dis[i]) {
      L = i;
    }
  }
  dfs(L, 0);
  for (int i = 1; i <= n; i++) {
    if (dis[R] < dis[i]) {
      R = i;
    }
  }
  int diameter = dis[R] - 1;

  std::vector<bool> vis(n + 1);
  std::vector<int> disOnDiameter(n + 1);
  std::vector<int> side(n + 1);
  int pivot = R, cnt = 0;
  while (pivot) {
    vis[pivot] = true;
    if (diameter - cnt > cnt) {
      side[pivot] = L;
      disOnDiameter[pivot] = diameter - cnt;
    } else {
      side[pivot] = R;
      disOnDiameter[pivot] = cnt;
    }
    pivot = nxt[pivot];
    cnt++;
  }

  std::priority_queue<std::pair<int, int>> pq;
  std::vector<int> bln(n + 1);
  std::function<void(int, int, int)> dfs2 = [&](int u, int frm, int rt) {
    dis[u] = dis[frm] + 1;
    vis[u] = true;
    bln[u] = rt;
    if (u != rt) {
      pq.emplace(dis[u] + disOnDiameter[rt] - 1, u);
    }
    for (auto v : g[u]) {
      if (vis[v] || v == frm) {
        continue;
      }
      dfs2(v, u, rt);
    }
  };

  pivot = R;
  while (pivot) {
    dfs2(pivot, 0, pivot);
    pivot = nxt[pivot];
  }

  i64 ans = 0;
  std::vector<std::tuple<int, int, int>> opt;
  while (!pq.empty()) {
    opt.emplace_back(side[bln[pq.top().second]], pq.top().second, pq.top().second);
    ans += pq.top().first;
    pq.pop();
  }

  pivot = R, cnt = 0;
  while (nxt[pivot]) {
    opt.emplace_back(pivot, L, pivot);
    ans += diameter - cnt;
    pivot = nxt[pivot];
    cnt++;
  }

  std::cout << ans << "\n";
  for (auto i : opt) {
    std::cout << std::get<0>(i) << " " << std::get<1>(i) << " " << std::get<2>(i) << "\n";
  }

  return 0;
}
