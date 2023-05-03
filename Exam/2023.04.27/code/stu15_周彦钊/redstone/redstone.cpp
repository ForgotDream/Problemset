#include <bits/stdc++.h>

using i64 = long long;

namespace myFile {
void useFileIO() {
  freopen("redstone.in", "r", stdin);
  freopen("redstone.out", "w", stdout);
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
  
  std::vector<i64> spfa(int s, std::vector<int> &pre) {
    pre.resize(n);
    std::vector<i64> dis(n, -INF);
    std::vector<bool> vis(n, false);
    std::queue<int> q;
    
    q.push(s), dis[s] = 0;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      vis[u] = false;
      for (auto i : e[u]) {
        int v = edges[i].v;
        i64 w = edges[i].w;
        if (dis[v] < dis[u] + w) {
          dis[v] = dis[u] + w;
          pre[v] = u;
          if (!vis[v]) {
            vis[v] = true;
            q.push(v);
          }
        }
      }
    }
    
    return dis;
  }
};

int main() {
  myFile::useFileIO();
  
  int n;
  fastIO::read(n);
  
  Graph g(n);
  for (int i = 1; i <= n; i++) {
    int t, c;
    fastIO::read(t, c);
    if (c == 0) {
      g.insert(0, i, t);
    } else {
      while (c--) {
        int p;
        fastIO::read(p);
        g.insert(p, i, t);
      }
    }
  }
  
  std::vector<int> pre;
  auto dis = g.spfa(0, pre);
  i64 preAns = *std::max_element(dis.begin(), dis.end());
  
  std::vector<int> mask(n + 1);
  int cnt = 0;
  for (int i = 1; i <= n; i++) {
    if (dis[i] == preAns) {
      int pivot = i;
      ++cnt;
      while (pivot) {
        mask[pivot]++;
        pivot = pre[pivot];
      }
    }
  }
  
  std::vector<int> ans;
  for (int i = 1; i <= n; i++) {
    if (mask[i] == cnt) {
      ans.push_back(i);
    }
  }
  
  printf("%lld\n%d\n", preAns, (int) ans.size());
  for (int i = 0; i < ans.size(); i++) {
    printf("%d ", ans[i]);
  }
  putchar('\n');
  
  return 0;
}
