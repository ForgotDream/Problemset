/*
 * @file    P1600 [NOIP2016 提高组] 天天爱跑步.cpp
 * @author  ForgotDream
 * @brief   Segment Tree Merge
 * @date    2023-12-30
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 3e5 + 50;
int n, m, w[N];
std::vector<int> adj[N];

namespace LCA {
int st[20][N], dfn[N], clk, dep[N], fa[N];
void dfs(int u, int frm) {
  st[0][dfn[u] = ++clk] = frm;
  dep[u] = dep[frm] + 1, fa[u] = frm;
  for (auto v : adj[u]) {
    if (v == frm) continue;
    dfs(v, u);
  }
}
inline int cmp(int u, int v) { return dfn[u] < dfn[v] ? u : v; }
void init() {
  dfs(1, 0);
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
}  // namespace LCA
using LCA::getLCA, LCA::dep, LCA::fa;

struct SegTree {
  struct Node {
    int lc, rc, sum;
  } tree[N << 5];
  int cnt;
  inline int &lc(int u) { return tree[u].lc; }
  inline int &rc(int u) { return tree[u].rc; }
  inline void pushup(int u) { tree[u].sum = tree[lc(u)].sum + tree[rc(u)].sum; }
  void modify(int tar, int s, int t, int &u, int val) {
    if (!u) u = ++cnt;
    if (s == t) return tree[u].sum += val, void();
    int mid = (s + t) >> 1;
    if (mid >= tar) modify(tar, s, mid, lc(u), val);
    else modify(tar, mid + 1, t, rc(u), val);
    pushup(u);
  }
  int query(int tar, int s, int t, int u) {
    if (!u) return 0;
    if (s == t) return tree[u].sum;
    int mid = (s + t) >> 1;
    if (mid >= tar) return query(tar, s, mid, lc(u));
    else return query(tar, mid + 1, t, rc(u));
  }
  int merge(int s, int t, int u, int v) {
    if (!u || !v) return u + v;
    if (s == t) return tree[u].sum += tree[v].sum, u;
    int mid = (s + t) >> 1;
    lc(u) = merge(s, mid, lc(u), lc(v));
    rc(u) = merge(mid + 1, t, rc(u), rc(v));
    pushup(u);
    return u;
  }
} seg;
int rt[N];

int ans[N];
void dfs(int u, int frm) {
  for (auto v : adj[u]) {
    if (v == frm) continue;
    dfs(v, u), rt[u] = seg.merge(-n, n, rt[u], rt[v]);
  }
  if (w[u] && dep[u] + w[u] <= n) ans[u] += seg.query(dep[u] + w[u], -n, n, rt[u]);
  ans[u] += seg.query(dep[u] - w[u], -n, n, rt[u]);
}

void solve() {
  std::cin >> n >> m;
  for (int i = 1, u, v; i < n; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
  }
  for (int i = 1; i <= n; i++) std::cin >> w[i];

  LCA::init();

  for (int i = 1, u, v, lca; i <= m; i++) {
    std::cin >> u >> v, lca = getLCA(u, v);
    seg.modify(dep[u], -n, n, rt[u], 1);
    seg.modify(2 * dep[lca] - dep[u], -n, n, rt[v], 1);
    seg.modify(dep[u], -n, n, rt[lca], -1);
    seg.modify(2 * dep[lca] - dep[u], -n, n, rt[fa[lca]], -1);
  }
  dfs(1, 0);

  for (int i = 1; i <= n; i++) std::cout << ans[i] << " \n"[i == n];
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
