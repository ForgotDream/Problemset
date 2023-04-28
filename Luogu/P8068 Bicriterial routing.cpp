/**
 * @file    P8068 Bicriterial routing.cpp
 * @author  ForgotDream
 * @brief   SSSP + DP
 * @date    2023-04-28
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
  static constexpr int INF = 1e9;
  struct Edge {
    int u, v, w, t;
    Edge(int _u = 0, int _v = 0, int _w = 0, int _t = 0) : u(_u), v(_v), w(_w), t(_t) {}
  };
  int n;
  std::vector<Edge> edges;
  std::vector<std::vector<int>> e;

  Graph(int _n) : n(_n) {
    e.resize(n);
    return;
  }

  void add(int u, int v, int w, int t) {
    edges.emplace_back(u, v, w, t);
    e[u].push_back(edges.size() - 1);
    return;
  }

  auto spfa(int s) {
    std::vector dis(n, std::vector<int>(10001, INF));
    std::vector<bool> vis(n, false);
    std::queue<int> q;

    dis[s][0] = 0, q.push(s);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      vis[u] = false;
      for (auto i : e[u]) {
        int v = edges[i].v, w = edges[i].w, t = edges[i].t;
        for (int k = 10000; k >= w; k--) {
          if (dis[v][k] > dis[u][k - w] + t) {
            dis[v][k] = dis[u][k - w] + t;
            if (!vis[v]) {
              vis[v] = true, q.push(v);
            }
          }
        }
      }
    }

    return dis;
  }
  
};

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  
  int n, m, s, t;
  std::cin >> n >> m >> s >> t;

  Graph g(n + 1);
  for (int i = 0; i < m; i++) {
    int u, v, w, t;
    std::cin >> u >> v >> w >> t;
    g.add(u, v, w, t);
    g.add(v, u, w, t);
  }

  auto dis = g.spfa(s);
  int ans = 0, min = 1e9;

  for (int i = 0; i <= 10000; i++) {
    if (min > dis[t][i]) {
      min = dis[t][i];
      ans++;
    }
  }

  std::cout << ans << "\n";

  return 0;
}