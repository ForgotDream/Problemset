/**
 * @file    P2323 [HNOI2006] 公路修建问题.cpp
 * @author  ForgotDream
 * @brief   MST
 * @date    2023-11-26
 */
#include <bits/stdc++.h>

using i64 = int64_t;

constexpr int N = 2e4 + 50;
int n, k, m;
struct Edge {
  int u, v, w1, w2, id;
  Edge() = default;
  Edge(int u, int v, int w1, int w2, int id) : u(u), v(v), w1(w1), w2(w2), id(id) {}
};
std::vector<Edge> edges;
bool used[N];
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
  std::cin >> n >> k >> m;
  for (int i = 1, u, v, w1, w2; i < m; i++) {
    std::cin >> u >> v >> w1 >> w2;
    edges.emplace_back(u, v, w1, w2, i);
  }
  std::sort(edges.begin(), edges.end(), [](auto lhs, auto rhs) {
    return lhs.w1 < rhs.w1;
  });
  int cnt = 0, ans = 0;
  std::map<int, int> mp;
  for (auto [u, v, w1, w2, id] : edges) {
    if (dsu.merge(u, v)) {
      ans = std::max(ans, w1), cnt++, used[id] = true, mp[id] = 1;
      if (cnt == k) break;
    }
  }
  std::sort(edges.begin(), edges.end(), [](auto lhs, auto rhs) {
    return lhs.w2 < rhs.w2;
  });
  for (auto [u, v, w1, w2, id] : edges) {
    if (used[id]) continue;
    if (dsu.merge(u, v)) {
      ans = std::max(ans, w2), cnt++, mp[id] = 2;
      if (cnt == n - 1) break;
    }
  }
  std::cout << ans << "\n";
  for (auto [t, p] : mp) std::cout << t << " " << p << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
