/**
 * @file    P2502 旅行.cpp
 * @author  ForgotDream
 * @brief   DSU + MST
 * @date    2023-06-16
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int inf = 1e9;

struct Edge {
  int u, v, w;
  Edge(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}
  bool operator<(const Edge &rhs) { return w < rhs.w; }
};
struct DSU {
  std::vector<int> fa;
  DSU(int n = 0) { set(n); }
  void set(int n) { fa.resize(n), std::iota(fa.begin(), fa.end(), 0); }
  int find(int u) { return u == fa[u] ? u : fa[u] = find(fa[u]); }
  bool merge(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) { return false; }
    fa[u] = v;
    return true;
  }
};

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  std::vector<Edge> edges;
  for (int i = 0; i < m; i++) {
    int u, v, w;
    std::cin >> u >> v >> w;
    u--, v--;
    edges.emplace_back(u, v, w);
  }

  int s, t;
  std::cin >> s >> t;
  s--, t--;

  // check
  std::vector<bool> vis(n);
  bool flg = [&]() {
    DSU dsu(n);
    for (int i = 0; i < m; i++) { dsu.merge(edges[i].u, edges[i].v); }
    if (dsu.find(s) != dsu.find(t)) { return false; }
    for (int i = 0; i < n; i++) {
      if (dsu.find(i) == dsu.find(s)) { vis[i] = true; }
    }
    return true;
  }();
  if (!flg) {
    std::cout << "IMPOSSIBLE\n";
    return 0;
  }

  std::sort(edges.begin(), edges.end());
  std::vector<std::pair<int, int>> ans;
  for (int i = 0; i < m; i++) {
    if (!vis[edges[i].u] || !vis[edges[i].v]) { continue; }
    DSU dsu(n);
    int max = edges[i].w, min = inf;
    for (int j = i; j >= 0; j--) {
      int u = edges[j].u, v = edges[j].v, w = edges[j].w;
      if (!vis[u] || !vis[v]) { continue; }
      if (dsu.merge(u, v)) {
        min = w;
        if (dsu.find(s) == dsu.find(t)) {
          ans.emplace_back(max, min);
          break;
        }
      }
    }
  }

  int idx = -1;
  double chk = inf;
  for (int i = 0; i < ans.size(); i++) {
    int max = ans[i].first, min = ans[i].second;
    if (idx == -1 || 1. * max / min < chk) { idx = i, chk = 1. * max / min; }
  }

  int max = ans[idx].first, min = ans[idx].second;
  int g = std::__gcd(max, min);

  if (max % min == 0) {
    std::cout << max / min << "\n";
  } else {
    std::cout << max / g << "/" << min / g << "\n";
  }

  return 0;
}