/*
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2023-12-27
 */
#include <bits/stdc++.h>

using i64 = long long;
using pii = std::pair<int, int>;

constexpr int N = 2e5 + 50;
int n, m, a[N];
std::vector<pii> adj[N / 1000];

inline int calc(int cur, int lst) { return (lst % (1 << 30)) ^ cur; }

namespace LCA {
int st[20][N], dfn[N], clk;
i64 dep[N];
void dfs(int u, int frm) {
  st[0][dfn[u] = ++clk] = frm;
  for (auto [v, w] : adj[u]) {
    if (v == frm) continue;
    dep[v] = dep[v] + w, dfs(v, u);
  }
}
inline int cmp(int u, int v) { return dfn[u] < dfn[v] ? u : v; }
void init() {
  for (int i = 1; i <= std::__lg(n); i++) {
    for (int j = 1; j <= n - (1 << i) + 1; j++) {
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
inline i64 getDis(int u, int v) {
  int lca = getLCA(u, v);
  return dep[u] + dep[v] - 2 * dep[lca];
}
}  // namespace LCA
using LCA::getLCA, LCA::getDis;

int bln[N], lp[N], rp[N];
i64 dis[N];
void dfs1(int u, int frm) {
  for (auto [v, w] : adj[u]) {
    
  }
}

void solve() {
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  for (int i = 1, u, v, w; i < n; i++) {
    std::cin >> u >> v >> w;
    adj[u].emplace_back(v, w), adj[v].emplace_back(u, w);
  }

  LCA::dfs(1, 0), LCA::init();

  int blk = std::sqrt(n), bcnt = n / blk + 1;
  for (int i = 1; i <= n; i++) bln[i] = (i - 1) / blk + 1;
  for (int i = 1; i <= bcnt; i++) lp[i] = (i - 1) * blk + 1, rp[i] = i * blk;

  for (int i = 1; i <= bcnt; i++) {
    for (int j = lp[i]; j <= rp[i]; j++) {
      
    }
  }

  i64 lst = 0;
  for (int i = 1, opt, l, r, v; i <= m; i++) {
    std::cin >> opt;
    if (opt == 1) {
      std::cin >> l >> r >> v;
      l = calc(l, lst), r = calc(r, lst), v = calc(v, lst);
    } else {
      std::cin >> v, v = calc(v, lst);
    }
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
