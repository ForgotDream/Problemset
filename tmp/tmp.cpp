/*
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2023-12-29
 */
#include <bits/stdc++.h>

using i64 = long long;

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

void solve() {
  std::cin >> n >> m >> k >> q;
  for (int i = 1; i <= m; i++) {
    auto &[u, v, w] = edges[i];
    std::cin >> u >> v >> w;
  }
  for (int i = 1; i <= n; i++) std::cin >> col[i];

  std::sort(edges + 1, edges + m + 1);
  int cnt = n;
  for (int i = 1; i <= m; i++) {
    auto [u, v, w] = edges[i];
    int fu = dsu.find(u), fv = dsu.find(v);
    if (fu == fv) continue;
    cnt++, dsu.fa[cnt] = dsu.fa[fu] = dsu.fa[fv] = cnt;
    if (cnt == 2 * n - 1) break;
  }

  for (int i = 1, u, v; i <= q; i++) {
    std::cin >> u >> v;
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
