#include <bits/stdc++.h>
#include <iostream>
#include <vector>

using i64 = long long;

struct Graph {
  int n, m;
  std::vector<std::vector<std::pair<int, int>>> e;
  
  Graph(const int &n, const int &m) {
    this->n = n;
    this->m = m;
    e.resize(n + 1);
    return;
  }
  
  void add(int u, int v, int w) {
    e[u].emplace_back(v, w);
    return;
  }
};

struct Edge {
  int from, to, w;
  Edge(int u, int v, int w) : from(u), to(v), w(w) {}
};

struct DSU {
  int n, cnt;
  std::vector<int> fa;
  
  DSU(int n) {
    this->n = n;
    this->cnt = n;
    fa.resize(n);
    std::iota(fa.begin(), fa.end(), 0);
    return;
  }
  
  int get(int u) {
    return (u == fa[u]) ? u : fa[u] = get(fa[u]);
  }
  
  int merge(int u, int v) {
    int fau = get(u), fav = get(v);
    if (fau == fav) {
      return cnt;
    }
    fa[fau] = fav;
    return --cnt;
  }
};

int main() {
  // freopen("graph.in", "r", stdin);
  // freopen("graph.out", "w", stdout);
  
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  
  int n, m;
  std::cin >> n >> m;
  
  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }
  Graph G(n, m);
  std::vector<Edge> edge;
  for (int i = 1; i <= m; i++) {
    int u, v, w;
    std::cin >> u >> v >> w;
    edge.emplace_back(u, v, w);
  }
  
  if (n == 1) {
    std::cout << "0.00" << "\n";
    return 0;
  } else if (n == 2) {
    std::cout << std::fixed << std::setprecision(2) << (double(a[0] + a[1]) / G.e[1][0].second) << "\n";
    return 0;
  }
  
  double ans = 0;
  for (int i = 0; i < (1 << n) - 1; i++) {
    DSU dsu(n);
    int cnt = 0;
    double ver = 0, e = 0;
    for (auto curEdge : edge) {
      if ((i & (1 << (curEdge.from - 1))) || (i & (1 << (curEdge.to - 1)))) {
        continue;
      }
      e += curEdge.w;
      dsu.merge(curEdge.from, curEdge.to);
    }
    for (int j = 0; j < n; j++) {
      if ((1 << j) & i) {
        cnt++;
        continue;
      }
      ver += a[j];
    }
    if (dsu.cnt != cnt + 1 || cnt + 1 == n) {
      continue;
    }
    ans = std::max(ans, ver / e);
  }
  
  std::cout << std::fixed << std::setprecision(2) << ans << "\n";
  
  return 0;
}
