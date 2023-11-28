/**
 * @file    P4047 [JSOI2010] 部落划分.cpp
 * @author  ForgotDream
 * @brief   MST
 * @date    2023-11-26
 */
#include <bits/stdc++.h>

using i64 = int64_t;
using f64 = double;

constexpr int N = 1050;
int n, k, x[N], y[N];
struct Edge {
  int u, v;
  f64 w;
  Edge() = default;
  Edge(int u, int v, f64 w) : u(u), v(v), w(w) {}
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
  std::cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    std::cin >> x[i] >> y[i];
    for (int j = 1; j < i; j++) edges.emplace_back(i, j, std::hypot(x[i] - x[j], y[i] - y[j]));
  }
  std::sort(edges.begin(), edges.end());
  int cnt = 0;
  f64 ans = 0;
  for (auto [u, v, w] : edges) {
    if (dsu.merge(u, v)) {
      ans = w, cnt++;
      if (cnt == n - k + 1) break;
    }
  }
  std::cout << std::fixed << std::setprecision(2) << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
