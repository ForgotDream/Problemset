/**
 * @file    P5764 新年好.cpp
 * @author  ForgotDream
 * @brief   SSSP
 * @date    2023-04-23
 */
#include <bits/stdc++.h>

using i64 = long long;
using i64u = unsigned long long;
using f80 = long double;

namespace MyFile {
void useFileInuput() {
  #ifndef ONLINE_JUDGE
  freopen("tmp.in", "r", stdin);
  freopen("tmp.out", "w", stdout);
  #endif
  return;
}
}

struct Graph {
  std::vector<std::vector<std::pair<int, int>>> e;
  int n;

  Graph(const int &n) : n(n + 1) {
    e.resize(n + 1);
    return;
  }

  void add(const int &u, const int &v, const int &w) {
    e[u].emplace_back(v, w);
    e[v].emplace_back(u, w);
    return;
  }

  std::vector<int> dijkstra(const int &s) {
    std::vector<int> dis(n, 1e9);
    std::vector<bool> vis(n, false);

    std::priority_queue<std::pair<int, int>,
                        std::vector<std::pair<int, int>>,
                        std::greater<std::pair<int, int>>> pq;

    pq.emplace(0, s);
    dis[s] = 0;
    while (!pq.empty()) {
      int u = pq.top().second;
      pq.pop();
      if (vis[u]) {
        continue;
      }
      vis[u] = true;
      for (auto i : e[u]) {
        int v = i.first, w = i.second;
        if (dis[v] > dis[u] + w) {
          dis[v] = dis[u] + w;
          pq.emplace(dis[v], v);
        }
      }
    }

    return dis;
  }
};

int dfs(int u, 
        int cnt,
        int pre, 
        const std::vector<int> &target, 
        const std::vector<int> &bdis,
        const std::vector<std::vector<int>> &dis) {
  if (cnt == 5) {
    return 0;
  }
  static std::vector<bool> vis(5);
  int res = 1e9;
  if (u == 1) {
    for (int i = 0; i < 5; i++) {
      int v = target[i], w = bdis[v];
      vis[i] = true;
      res = std::min(res, w + dfs(v, cnt + 1, i, target, bdis, dis));
      vis[i] = false;
    }
  } else {
    for (int i = 0; i < 5; i++) {
      if (vis[i]) {
        continue;
      }
      int v = target[i], w = dis[pre][v];
      vis[i] = true;
      res = std::min(res, w + dfs(v, cnt + 1, i, target, bdis, dis));
      vis[i] = false;
    }
  }
  return res;
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  std::vector<int> target(5);
  for (auto &i : target) {
    std::cin >> i;
  }

  Graph g(n);
  for (int i = 0; i < m; i++) {
    int u, v, w;
    std::cin >> u >> v >> w;
    g.add(u, v, w);
  }

  std::vector dis(5, std::vector<int>());
  for (int i = 0; i < 5; i++) {
    dis[i] = g.dijkstra(target[i]);
  }
  auto bdis = g.dijkstra(1);

  std::cout << dfs(1, 0, 0, target, bdis, dis) << "\n";

  return 0;
}