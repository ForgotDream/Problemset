/*
 * @file    P3665 [USACO17OPEN] Switch Grass P.cpp
 * @author  ForgotDream
 * @brief   Kruskal
 * @date    2023-12-30
 */
#include <bits/stdc++.h>

using i64 = long long;
using pii = std::pair<int, int>;

constexpr int N = 2e5 + 50;
int n, m, k, q;
int col[N];

struct Edge {
  int u, v, w;
  bool operator<(const Edge &rhs) const { return w < rhs.w; }
} edges[N];
struct DSU {
  int fa[N];
  void init(int _n) { std::iota(fa + 1, fa + _n + 1, 1); }
  int find(int u) { return u == fa[u] ? u : fa[u] = find(fa[u]); }
} dsu;

int head[N], tail[N];
std::vector<pii> adj[N];

void solve() {
  std::cin >> n >> m >> k >> q;
  for (int i = 1; i <= m; i++) {
    auto &[u, v, w] = edges[i];
    std::cin >> u >> v >> w;
  }
  for (int i = 1; i <= n; i++) std::cin >> col[i];

  std::iota(head + 1, head + n + 1, 1);
  std::iota(tail + 1, tail + n + 1, 1);

  std::sort(edges + 1, edges + m + 1);
  int cnt = 0;
  dsu.init(n);
  for (int i = 1; i <= m; i++) {
    auto [u, v, w] = edges[i];
    u = dsu.find(u), v = dsu.find(v);
    if (u != v) {
      cnt++, tail[v] = tail[u], dsu.fa[u] = v;
      adj[head[v]].emplace_back(tail[u], w);
      adj[tail[u]].emplace_back(head[v], w);
    }
    if (cnt == n - 1) break;
  }

  std::multiset<int> s;
  for (int u = 1; u <= n; u++) {
    for (auto [v, w] : adj[u]) {
      if (col[u] != col[v] && u < v) s.insert(w);
    }
  }
  
  for (int i = 1, u, p; i <= q; i++) {
    std::cin >> u >> p;
    for (auto [v, w] : adj[u]) {
      if (col[u] != col[v]) s.erase(s.find(w));
      if (p != col[v]) s.insert(w);
    }
    col[u] = p;
    std::cout << *s.begin() << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
