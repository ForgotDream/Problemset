#include <bits/stdc++.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>

using i64 = long long;

struct Graph {
  const int INF = 0x3f3f3f3f;
  int n, m;
  std::vector<std::vector<std::pair<int, int>>> e;
  std::vector<int> dis;
  std::vector<bool> vis;
  
  Graph(int n, int m = 0) {
    this->n = n;
    this->m = m;
    e.resize(n);
    dis.resize(n);
    vis.resize(n);
    return;
  }
  
  void add(int u, int v, int w) {
    e[u].emplace_back(v, w);
    return;
  }
  
  int dijkstra(int s, int t) {
    dis.assign(n, INF);
    vis.assign(n, false);
    dis[s] = 0;
    
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> q;
    q.emplace(0, s);
    
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
    
    return dis[t];
  }
};

int main() {
  freopen("egypt.in", "r", stdin);
  freopen("egypt.out", "w", stdout);
  
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  
  int n, m;
  std::cin >> n >> m;
  
  Graph G(n * (n + 1) * (2 * n + 1) / 6 + 50);
  
  int cnt = 0;
  std::vector<std::vector<std::vector<int>>> mp(n + 1), t(n + 1);
  for (int k = 1; k <= n; k++) {
    int len = n - k + 1;
    
    mp[k].resize(len, std::vector<int>(len));
    t[k].resize(len, std::vector<int>(len));
    
    for (int i = 0; i < len; i++) {
      for (int j = 0; j < len; j++) {
        mp[k][i][j] = ++cnt;
        std::cin >> t[k][i][j];
      }
    }
  }
  
  std::vector<std::vector<int>> d1 = {{0, 0}, {1, 1}, {1, 0}, {0, 1}};
  std::vector<std::vector<int>> d2 = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
  
  for (int k = 1; k <= n; k++) {
    int len = n - k + 1;
    
    for (int i = 0; i < len; i++) {
      for (int j = 0; j < len; j++) {
        if (k != 1) {
          for (auto p : d1) {
            int dx = i + p[0], dy = j + p[1];
            G.add(mp[k - 1][dx][dy], mp[k][i][j], t[k - 1][dx][dy]);
          }
        }
        
        for (auto p : d2) {
          int dx = i + p[0], dy = j + p[1];
          if (dx < 0 || dy < 0 || dx >= len || dy >= len) {
            continue;
          }
          G.add(mp[k][i][j], mp[k][dx][dy], t[k][i][j]);
        }
      }
    }
  }
  
  for (int i = 1; i <= m; i++) {
    int sfl, sx, sy, tfl, tx, ty, ti;
    std::cin >> sfl >> sx >> sy >> tfl >> tx >> ty >> ti;
    G.add(mp[sfl][sx - 1][sy - 1], mp[tfl][tx - 1][ty - 1], ti + t[sfl][sx - 1][sy - 1]);
  }
  
  std::cout << G.dijkstra(mp[1][0][0], mp[n][0][0]) + t[n][0][0] << "\n";
  
  return 0;
}
