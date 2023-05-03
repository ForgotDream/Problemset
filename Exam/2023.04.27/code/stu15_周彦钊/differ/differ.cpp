#include <bits/stdc++.h>

using i64 = long long;

namespace myFile {
void useFileIO() {
  freopen("differ.in", "r", stdin);
  freopen("differ.out", "w", stdout);
  return;
}
}

struct Graph {
  static constexpr i64 INF = 1e18;
  struct Edge {
    int u, v;
    i64 w;
    Edge(int _u, int _v, i64 _w) : u(_u), v(_v), w(_w) {}
  };
  int n;
  std::vector<Edge> edges;
  std::vector<std::vector<int>> e;
  
  Graph(int _n) : n(_n + 1) {
    e.resize(n);
    return;
  }
  
  void insert(int u, int v, int w) {
    edges.emplace_back(u, v, w);
    e[u].push_back(edges.size() - 1);
    return;
  }
  
  void add(int u, int v, int w) {
    insert(u, v, w), insert(v, u, w);
    return;
  }
  
  std::vector<i64> spfa(int s) {
    std::vector<i64> dis(n, INF);
    std::vector<bool> vis(n, false);
    std::queue<int> q;
    
    dis[s] = 0;
    q.push(s);
    while (!q.empty()) {
      int u = q.front();
      vis[u] = false;
      q.pop();
      for (auto i : e[u]) {
        int v = edges[i].v, w = edges[i].w;
        if (dis[v] > dis[u] + w) {
          dis[v] = dis[u] + w;
          if (!vis[v]) {
            vis[v] = true, q.push(v);
          }
        }
      }
    }
    
    return dis;
  }
};

int main() {
  myFile::useFileIO();
  
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  
  constexpr i64 INF = 1e18;
 
  int n, m;
  std::cin >> n >> m;
  
  Graph g(n);
  for (int i = 0; i < m; i++) {
    int opt, u, v, w;
    std::cin >> opt >> u >> v >> w;
    if (opt == 0) {
      g.insert(v, u, w);
    } else if (opt == 1) {
      g.insert(u, v, -w);
    } else {
      g.insert(v, u, w);
      g.insert(u, v, -w);
    }
  }
  
  int q;
  std::cin >> q;
  
  std::vector<std::vector<i64>> dis(n + 1);
  for (int i = 1; i <= n; i++) {
    dis[i] = g.spfa(i);
  }
  
  while (q--) {
    int u, v;
    std::cin >> u >> v;
    if (dis[v][u] == INF) {
      std::cout << "Infinity\n";
    } else {
      std::cout << dis[v][u] << "\n";
    }
  }
  
  return 0;
}
