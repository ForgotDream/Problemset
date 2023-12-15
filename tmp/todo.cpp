/**
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2023-12-15
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e5 + 50;
int n, m, q, a[N];
struct Edge {
  int u, v, w;
  bool operator<(const Edge &rhs) { return w < rhs.w; }
};
std::vector<Edge> edges;
struct DSU {
  int fa[N];
  DSU() { std::iota(fa, fa + N, 0); }
  int find(int u) { return u == fa[u] ? u : fa[u] = find(u); }
  bool merge(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return false;
    fa[u] = v;
    return true;
  }
} dsu;
std::vector<int> adj[N];
int val[N];
int dfn[N], clk, st[20][N];
void dfs(int u, int frm) {
  st[0][dfn[u] = ++clk] = frm;
  for (auto v : adj[u]) {
    if (v == frm) continue;
    dfs(v, u);
  }
}
inline int cmp(int u, int v) { return dfn[u] < dfn[v] ? u : v; }
void init() {
  for (int i = 1; i <= std::__lg(m); i++) {
    for (int j = 1; j <= m - (1 << i) + 1; j++) {
      st[i][j] = cmp(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
    }
  }
}
inline int getLCA(int u, int v) {
  if (u == v) return u;
  u = dfn[u], v = dfn[v];
  if (u > v) std::swap(u, v);
  int d = std::__lg(v - u++);
  return cmp(st[d][u], st[d][v - (1 << d) + 1]);
}
void solve() {
  std::cin >> n >> m >> q;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  edges.resize(m);
  for (auto &[u, v, w] : edges) std::cin >> u >> v >> w;
  std::sort(edges.begin(), edges.end());
  int cnt = n;
  for (auto [u, v, w] : edges) {
    int fu = dsu.find(u), fv = dsu.find(v);
    if (fu != fv) {
      cnt++;
      dsu.fa[fu] = dsu.fa[fv] = cnt;
      adj[fu].push_back(cnt), adj[fv].push_back(cnt);
      adj[cnt].push_back(fu), adj[cnt].push_back(fv);
      val[cnt] = w;
    }
    if (cnt == 2 * n - 1) break;
  }
  m = 2 * n - 1;
  for (int v, x, k; q; q--) {
    std::cin >> v >> x >> k;
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
