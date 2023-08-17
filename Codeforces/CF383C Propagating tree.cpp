/**
 * @file    CF383C Propagating tree.cpp
 * @author  ForgotDream
 * @brief   SegTree
 * @date    2023-08-15
 */
#include <bits/stdc++.h>
using i64 = long long;
constexpr int N = 2e5 + 50;
int n, m, a[N];
int dfn[N], idfn[N], siz[N], dep[N], clk;
std::vector<int> adj[N];
template<int N = 200050>
struct SegTree {
  int tag[N << 2], val[N << 2];
  SegTree() = default;
  int lc(int u) { return u << 1; }
  int rc(int u) { return u << 1 | 1; }
  void pushdown(int u) {
    if (!tag[u]) return;
    tag[lc(u)] += tag[u], tag[rc(u)] += tag[u];
    tag[u] = 0;
  }
  void build(int s, int t, int u) {
    if (s == t) return void(val[u] = a[idfn[s]]);
    int mid = (s + t) >> 1;
    build(s, mid, lc(u)), build(mid + 1, t, rc(u));
  }
  void modify(int l, int r, int s, int t, int u, int val) {
    if (l <= s && t <= r) return void(tag[u] += val);
    pushdown(u);
    int mid = (s + t) >> 1;
    if (mid >= l) modify(l, r, s, mid, lc(u), val);
    if (mid <  r) modify(l, r, mid + 1, t, rc(u), val);
  }
  int query(int tar, int s, int t, int u) {
    if (s == t) return val[u] + (dep[idfn[tar]] % 2 ? 1 : -1) * tag[u];
    pushdown(u);
    int mid = (s + t) >> 1;
    if (mid >= tar) return query(tar, s, mid, lc(u));
    else return query(tar, mid + 1, t, rc(u));
  }
};
SegTree seg;
void dfs(int u, int frm) {
  dfn[u] = ++clk, idfn[clk] = u;
  siz[u] = 1, dep[u] = dep[frm] + 1;
  for (auto v : adj[u]) {
    if (v == frm) continue;
    dfs(v, u), siz[u] += siz[v];
  }
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  for (int i = 1, u, v; i < n; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
  }
  dfs(1, 0);
  seg.build(1, n, 1);
  for (int i = 1; i <= m; i++) {
    int opt, u, val;
    std::cin >> opt;
    if (opt == 2) {
      std::cin >> u;
      std::cout << seg.query(dfn[u], 1, n, 1) << "\n";
    } else {
      std::cin >> u >> val;
      if (!(dep[u] % 2)) val = -val;
      seg.modify(dfn[u], dfn[u] + siz[u] - 1, 1, n, 1, val);
    }
  }
  return 0;
}