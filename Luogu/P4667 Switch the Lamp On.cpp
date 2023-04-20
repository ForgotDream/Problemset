/**
 * @file    P4667 Switch the Lamp On.cpp
 * @author  ForgotDream
 * @brief   最短路
 * @date    2023-03-29
 */
#include <bits/stdc++.h>

using i64 = long long;
using f80 = long double;

signed main() {
  #ifndef ONLINE_JUDGE
  freopen("tmp.in", "r", stdin);
  freopen("tmp.out", "w", stdout);
  #endif

  int n, m;
  std::cin >> n >> m;
  
  std::vector<std::vector<std::pair<int, int>>> e((n + 1) * (m + 1) + 50);
  auto add = [&](int u, int v, int w) -> void {
    e[u].emplace_back(v, w);
    e[v].emplace_back(u, w);
    return;
  };

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      char c;
      std::cin >> c;
      if (c == '/') {
        add((i + 1) * (m + 1) + j, i * (m + 1) + (j + 1), 0);
        add(i * (m + 1) + j, (i + 1) * (m + 1) + (j + 1), 1);
      } else {
        add((i + 1) * (m + 1) + j, i * (m + 1) + (j + 1), 1);
        add(i * (m + 1) + j, (i + 1) * (m + 1) + (j + 1), 0);
      }
    }
  }

  std::priority_queue<std::pair<int, int>,
                      std::vector<std::pair<int, int>>,
                      std::greater<std::pair<int, int>>> q;
  std::vector<int> dis((n + 1) * (m + 1) + 50, 1e9);
  std::vector<bool> vis((n + 1) * (m + 1) + 50);

  int s = 0, t = (n + 1) * (m + 1) - 1;
  q.emplace(0, s);
  dis[s] = 0;
  while (!q.empty()) {
    int u = q.top().second;
    q.pop();
    if (vis[u]) {
      continue;
    }
    vis[u] = true;
    for (auto i : e[u]) {
      int v = i.first, w = i.second;
      if (dis[v] > dis[u] + w) {
        dis[v] = dis[u] + w;
        q.emplace(dis[v], v);
      }
    }
  }

  if (dis[t] == 1e9) {
    std::cout << "NO SOLUTION" << "\n";
  } else {
    std::cout << dis[t] << "\n";
  }

  return 0;
}