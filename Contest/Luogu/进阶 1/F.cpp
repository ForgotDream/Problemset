#include <bits/stdc++.h>

using i64 = long long;

struct Graph {
  static constexpr int INF = 1e9;
  int n;
  struct Edge {
    int u, v, w;
    Edge (int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}
  };
  std::vector<Edge> edges;
  std::vector<std::vector<int>> e;

  Graph(int _n) : n(_n) {
    e.resize(n);
    return;
  }

  void add(int u, int v, int w = 0) {
    edges.emplace_back(u, v, w);
    e[u].push_back(edges.size() - 1);
    return;
  }

  void spfa(int s, const int &x, const int &k) {
    std::queue<int> q;
    std::vector<int> dis(n, INF), semi(n, INF);
    std::vector<bool> vis(n, false);

    q.push(s), dis[s] = 0;

    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (int i : e[u]) {
        int v = edges[i].v, w = edges[i].w;
        if (dis[v] > dis[u] + w) {
          semi[v] = dis[v];
          dis[v] = dis[u] + w;
          if (!vis[v]) {
            vis[v] = true, q.push(v);
          }
        } else if (semi[v] > dis[u] + w) {
          semi[v] = dis[u] + w;
        }
      }
    }

    return;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int n, m, k, x;
  std::cin >> n >> m >> k >> x;

  Graph g(n + 1);
  for (int i = 0; i < m; i++) {
    int u, v, w;
    std::cin >> u >> v >> w;
    g.add(u, v), g.add(v, u);
  }

  for (int i = 1; i <= n; i++) {
    
  }

  return 0;
}