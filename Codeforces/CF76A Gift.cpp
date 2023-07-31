/**
 * @file    CF76A Gift.cpp
 * @author  ForgotDream
 * @brief   Kruskal
 * @date    2023-07-28
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 250, M = 5e4 + 50;
int n, m;
i64 ans = 3e18, S, G;
struct Edge {
  int u, v, s, g;
  Edge() {}
  Edge(int _u, int _v, int _s, int _g) { u = _u, v = _v, s = _s, g = _g; }
  bool operator<(const Edge &rhs) const { return s < rhs.s; }
  bool operator==(const Edge &rhs) const { return s == rhs.s; }
  bool operator>(const Edge &rhs) const { return s > rhs.s; }
} edges[M];
struct DSU {
  int fa[N];
  DSU() { init(); }
  void init() { std::iota(fa, fa + N, 0); }
  int find(int u) { return u == fa[u] ? u : fa[u] = find(fa[u]); }
  bool merge(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return false;
    fa[u] = v;
    return true;
  }
} dsu;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n >> m >> S >> G;
  for (int i = 1; i <= m; i++) {
    auto &[u, v, s, g] = edges[i];
    std::cin >> u >> v >> s >> g;
  }

  std::sort(edges + 1, edges + m + 1, [&](auto lhs, auto rhs) {
    return lhs.g < rhs.g;
  });
  std::vector<Edge> t;
  for (int i = 1; i <= m; i++) {
    std::vector<Edge> tmp;
    auto cur = edges[i];
    auto it = std::upper_bound(t.begin(), t.end(), cur);
    t.emplace(it, cur);
    int max = 0;
    dsu.init();
    for (auto [u, v, s, g] : t) {
      if (dsu.merge(u, v)) {
        tmp.emplace_back(u, v, s, g);
        max = std::max(max, s);
      }
    }
    if (tmp.size() == n - 1) ans = std::min(ans, G * edges[i].g + S * max);
    t = tmp;
  }
  std::cout << (ans == 3e18 ? -1 : ans) << "\n";

  return 0;
}