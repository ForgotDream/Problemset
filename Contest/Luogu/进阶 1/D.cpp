#include <bits/stdc++.h>

using i64 = long long;

struct Graph {
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

  std::vector<int> bfs(int s) {
    std::queue<int> q;
    std::vector<int> dis(n, -1);

    q.push(s), dis[s] = 0;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (int i : e[u]) {
        int v = edges[i].v;
        if (dis[v] != -1) {
          continue;
        }
        dis[v] = dis[u] + 1;
        q.push(v);
      }
    }

    return dis;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int n;
  std::cin >> n;

  Graph g(n * n + 1);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= i; j++) {
      int c, u = (i - 1) * (i - 1) + 2 * j - 1;
      std::cin >> c;
      for (int p = 4; p; p >>= 1) {
        if (c >= p) {
          int v;
          if (p == 1) {
            v = u + 1;
          } else if (p == 2) {
            v = i * i + 2 * j;
          } else {
            v = u - 1;
          }
          g.add(u, v), g.add(v, u);
          c -= p;
        }
      }
    }
  }

  auto dis = g.bfs(1);
  int ans = 0;
  for (int i = 1; i <= n * n; i++) {
    if (dis[i] != -1) {
      ans++;
    }
  }

  std::cout << ans << "\n";

  return 0;
}