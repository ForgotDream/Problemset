/**
 * @file    P1073 最优贸易.cpp
 * @author  ForgotDream
 * @brief   分层图 + SSSP
 * @date    2023-04-24
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
  struct Edge {
    int u, v, w;
    Edge (const int &u, const int &v, const int &w) : u(u), v(v), w(w) {
      return;
    }
  };
  std::vector<Edge> edges;
  int n;
  std::vector<std::vector<int>> e;

  Graph(const int &n) : n(n + 1) {
    e.resize(n + 1);
    return;
  }

  void add(int u, int v, int w) {
    edges.emplace_back(u, v, w);
    e[u].emplace_back(edges.size() - 1);
    return;
  }

  std::vector<int> spfa(const int &s) {
    std::vector<int> dis(n, -1e9);
    std::vector<bool> vis(n, false);

    std::queue<int> q;
    q.push(s);
    dis[s] = 0, vis[s] = true;

    while (!q.empty()) {
      int u = q.front();
      q.pop(), vis[u] = false;
      for (auto i : e[u]) {
        int v = edges[i].v, w = edges[i].w;
        if (dis[v] < dis[u] + w) {
          dis[v] = dis[u] + w;
          if (!vis[v]) {
            q.push(v);
            vis[v] = true;
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

  int n, m;
  std::cin >> n >> m;

  Graph g(3 * n);
  std::vector<int> a(n + 1);
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i];
    g.add(i, i + n, -1 * a[i]);
    g.add(i + n, i + 2 * n, a[i]);
  }

  for (int i = 0; i < m; i++) {
    int u, v, w;
    std::cin >> u >> v >> w;
    g.add(u, v, 0);
    g.add(u + n, v + n, 0);
    g.add(u + 2 * n, v + 2 * n, 0);
    if (w == 2) {
      g.add(v, u, 0);
      g.add(v + n, u + n, 0);
      g.add(v + 2 * n, u + 2 * n, 0);
    }
  }

  std::cout << g.spfa(1)[3 * n] << "\n";

  return 0;
}