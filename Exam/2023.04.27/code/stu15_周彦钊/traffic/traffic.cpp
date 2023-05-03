#include <bits/stdc++.h>

using i64 = long long;

namespace myFile {
void useFileIO() {
  freopen("traffic.in", "r", stdin);
  freopen("traffic.out", "w", stdout);
  return;
}
}

namespace fastIO {
template<typename T>
void read(T &x) {
  x = 0;
  T f = 1;
  char c = getchar();
  while (!std::isdigit(c)) {
    if (c == '-') { f = -1; }
    c = getchar();
  }
  while (std::isdigit(c)) {
    x = 10 * x + c - '0';
    c = getchar();
  }
  x *= f;
  return;
}

template<typename T, typename ...arg>
void read(T &x, arg &...args) {
  read(x), read(args...);
  return;
}
}

struct Graph {
  struct Edge {
    int u, v;
    i64 w;
    Edge(int _u, int _v, i64 _w) : u(_u), v(_v), w(_w) {}
  };
  int n;
  std::vector<Edge> edges;
  std::vector<int> r, g;
  std::vector<std::vector<int>> e;
  
  Graph(int _n) : n(_n + 1) {
    e.resize(n);
    r.resize(n), g.resize(n);
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
  
  std::vector<i64> dijkstra(int s, int t) {
    std::vector<i64> dis(n, 1e18);
    std::vector<bool> vis(n, false);
    std::priority_queue<
      std::pair<int, int>,
      std::vector<std::pair<int, int>>,
      std::greater<std::pair<int, int>>
    > pq;
    
    dis[s] = 0, pq.emplace(0, s);
    
    while (!pq.empty()) {
      int u = pq.top().second;
      pq.pop();
      if (vis[u]) {
        continue;
      }
      vis[u] = true;
      for (auto i : e[u]) {
        int v = edges[i].v;
        i64 w = edges[i].w, cur = dis[u] + w;
        
        if (v != t && r[v] + g[v] && cur % (r[v] + g[v]) <= r[v]) {
          cur += (r[v] - cur % (r[v] + g[v]));  
        }
        
        if (dis[v] > cur) {
          dis[v] = cur;
          pq.emplace(dis[v], v);
        }
      }
    }
    
    return dis;
  }
};

int main() {
  myFile::useFileIO();
  
  int n, m, s, t;
  fastIO::read(n, m, s, t);
  
  Graph g(n);
  for (int i = 1; i <= n; i++) {
    fastIO::read(g.r[i], g.g[i]);
  }
  
  for (int i = 0; i < m; i++) {
    int u, v;
    i64 w;
    fastIO::read(u, v, w);
    g.add(u, v, w);
  }
  
  g.add(0, s, 0);
  auto dis = g.dijkstra(0, t);
  
  printf("%lld\n", dis[t]);
  
  return 0;
}
