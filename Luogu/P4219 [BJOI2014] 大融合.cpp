/*
 * @file    P4219 [BJOI2014] 大融合.cpp
 * @author  ForgotDream
 * @brief   BIT
 * @date    2023-12-26
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 50;
int n, q;
std::vector<int> adj[N];

struct Query {
  char opt;
  int u, v;
} qry[N];

struct DSU {
  int fa[N];
  void init(int n) { std::iota(fa + 1, fa + n + 1, 1); }
  int find(int u) { return u == fa[u] ? u : fa[u] = find(fa[u]); }
} dsu;

int fa[N], siz[N], dfn[N], clk;
void dfs(int u, int frm) {
  fa[u] = frm, siz[u] = 1, dfn[u] = ++clk;
  for (auto v : adj[u]) {
    if (v == frm) continue;
    dfs(v, u), siz[u] += siz[v];
  }
}
inline int in(int u) { return dfn[u]; }
inline int out(int u) { return dfn[u] + siz[u] - 1; }

struct BIT {
  int tree[N];
  inline void modify(int u, int val) {
    if (!u) return;
    for (int i = u; i <= n; i += i & -i) tree[i] += val;
  }
  inline i64 query(int u) {
    i64 res = 0;
    for (int i = u; i; i -= i & -i) res += tree[i];
    return res;
  }
  inline i64 query(int l, int r) { return query(r) - query(l - 1); }
} bit;

void solve() {
  std::cin >> n >> q;
  for (int i = 1; i <= q; i++) {
    auto &[opt, u, v] = qry[i];
    std::cin >> opt >> u >> v;
    if (opt == 'A') {
      adj[u].push_back(v), adj[v].push_back(u);
    }
  }

  dsu.init(n);
  for (int i = 1; i <= n; i++) if (!dfn[i]) dfs(i, 0);

  for (int i = 1; i <= n; i++) bit.modify(in(i), 1), bit.modify(in(fa[i]), -1);

  for (int i = 1; i <= q; i++) {
    auto [opt, u, v] = qry[i];
    if (dfn[u] < dfn[v]) std::swap(u, v);
    int fv = dsu.find(v);
    i64 tmp = bit.query(in(u), out(u));
    if (opt == 'Q') {
      std::cout << tmp * (bit.query(in(fv), out(fv)) - tmp) << "\n";
    } else {
      bit.modify(in(v), tmp), bit.modify(in(fa[fv]), -tmp);
      dsu.fa[u] = fv;
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
