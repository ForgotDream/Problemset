/**
 * @file    P5994 [PA2014] Kuglarz.cpp
 * @author  ForgotDream
 * @brief   Kruskal
 * @date    2023-11-29
 */
#include <bits/stdc++.h>

using i64 = int64_t;

constexpr int N = 2050;
int n;
struct Edge {
  int u, v, w;
  Edge() = default;
  Edge(int u, int v, int w) : u(u), v(v), w(w) {}
  bool operator<(const Edge &rhs) { return w < rhs.w; }
};
std::vector<Edge> edges;
struct DSU {
  int fa[N];
  DSU() { std::iota(fa, fa + N, 0); }
  int find(int u) { return u == fa[u] ? u : fa[u] = find(fa[u]); }
  bool merge(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return false;
    fa[u] = v;
    return true;
  }
} dsu;
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) {
    for (int j = i, w; j <= n; j++) {
      std::cin >> w, edges.emplace_back(i - 1, j, w);
    }
  }
  std::sort(edges.begin(), edges.end());
  int cnt = 0;
  i64 ans = 0;
  for (auto [u, v, w] : edges) {
    if (dsu.merge(u, v)) {
      ans += w, cnt++;
      if (cnt == n) break;
    }
  }
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
