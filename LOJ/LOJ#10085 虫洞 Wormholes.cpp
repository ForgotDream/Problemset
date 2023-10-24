/**
 * @file    LOJ#10085 虫洞 Wormholes.cpp
 * @author  ForgotDream
 * @brief   SPFA Check Circle
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
    int u, v, w;
    Edge(int _u = 0, int _v = 0, int _w = 0) : u(_u), v(_v), w(_w) {}
  };
  int n;
  std::vector<Edge> edges;
  std::vector<std::vector<int>> e;

  Graph(int _n) : n(_n) {
    e.resize(n);
    return;
  }

  void add(int u, int v, int w) {
    edges.emplace_back(u, v, w);
    e[u].push_back(edges.size() - 1);
    return;
  }

  bool findCircle(int s) {
    std::vector<bool> vis(n, false);
    std::vector<int> dis(n, 0);

    std::function<bool(int)> spfa = [&](int u) -> bool {
      vis[u] = true;

      for (auto i : e[u]) {
        int v = edges[i].v, w = edges[i].w;
        if (dis[v] > dis[u] + w) {
          dis[v] = dis[u] + w;
          if (vis[v]) {
            return true;
          } else if (spfa(v)) {
            return true;
          }
        }
      }

      vis[u] = false;
      return false;
    };

    return spfa(s);
  }
  
};

void solve() {
  constexpr int INF = 1e9;
  int n, m, w;
  std::cin >> n >> m >> w;

  Graph g(n + 1);
  for (int i = 0; i < m; i++) {
    int u, v, w;
    std::cin >> u >> v >> w;
    g.add(u, v, w), g.add(v, u, w);
  }
  for (int i = 0; i < w; i++) {
    int u, v, w;
    std::cin >> u >> v >> w;
    g.add(u, v, -w);
  }
  for (int i = 1; i <= n; i++) {
    g.add(0, i, -INF);
  }

  if (g.findCircle(0)) {
    std::cout << "YES\n";
  } else {
    std::cout << "NO\n";
  }

  return;
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  std::cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}