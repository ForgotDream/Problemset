/**
 * @file    P4556 [Vani有约会] 雨天的尾巴 /【模板】线段树合并.cpp
 * @author  ForgotDream
 * @brief   SegTree
 * @date    2023-07-27
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 50, C = 1e5;
int n, m, ans[N];
std::vector<int> adj[N];
struct LCA {
  int fa[N], top[N], son[N], siz[N], dep[N];
  void dfs1(int u, int frm) {
    fa[u] = frm, dep[u] = dep[frm] + 1, siz[u] = 1;
    for (auto v : adj[u]) {
      if (v == frm) continue;
      dfs1(v, u);
      siz[u] += siz[v];
      if (siz[v] > siz[son[u]]) son[u] = v;
    }
  }
  void dfs2(int u, int rt) {
    top[u] = rt;
    if (son[u]) dfs2(son[u], rt);
    for (auto v : adj[u]) {
      if (v == fa[u] || v == son[u]) continue;
      dfs2(v, v);
    }
  }
  int lca(int u, int v) {
    while (top[u] != top[v]) {
      if (dep[top[u]] < dep[top[v]]) std::swap(u, v);
      u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
  }
} lca;
struct SegTree {
  struct Node {
    int col = 0, val = 0, lc = 0, rc = 0;
  } tree[50 * N];
  int rt[N], cnt;
  int &lc(int u) { return tree[u].lc; }
  int &rc(int u) { return tree[u].rc; }
  void pushup(int u) {
    if (tree[lc(u)].val >= tree[rc(u)].val) 
      tree[u].val = tree[lc(u)].val, tree[u].col = tree[lc(u)].col;
    else 
      tree[u].val = tree[rc(u)].val, tree[u].col = tree[rc(u)].col;
  }
  int modify(int tar, int s, int t, int u, int val) {
    if (!u) u = ++cnt;
    if (s == tar && t == tar) {
      tree[u].val += val, tree[u].col = tar;
      return u;
    }
    int mid = (s + t) >> 1;
    if (mid >= tar) lc(u) = modify(tar, s, mid, lc(u), val);
    else rc(u) = modify(tar, mid + 1, t, rc(u), val);
    pushup(u);
    return u;
  }
  int merge(int s, int t, int u, int v) {
    if (!u || !v) return u ? u : v;
    if (s == t) {
      tree[u].val += tree[v].val;
      return u;
    }
    int mid = (s + t) >> 1;
    lc(u) = merge(s, mid, lc(u), lc(v));
    rc(u) = merge(mid + 1, t, rc(u), rc(v));
    pushup(u);
    return u;
  }
} seg;

void dfs(int u) {
  for (auto v : adj[u]) {
    if (v == lca.fa[u]) continue;
    dfs(v);
    seg.rt[u] = seg.merge(1, C, seg.rt[u], seg.rt[v]);
  }
  if (SegTree::Node f; (f = seg.tree[seg.rt[u]]).val) ans[u] = f.col;
  // std::cerr << seg.tree[seg.rt[u]].col << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n >> m;
  for (int i = 1, u, v; i < n; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  lca.dfs1(1, 0), lca.dfs2(1, 1);

  while (m--) {
    int u, v, w;
    std::cin >> u >> v >> w;
    int f = lca.lca(u, v), g = lca.fa[f];
    seg.rt[u] = seg.modify(w, 1, C, seg.rt[u], 1);
    seg.rt[v] = seg.modify(w, 1, C, seg.rt[v], 1);
    seg.rt[f] = seg.modify(w, 1, C, seg.rt[f], -1);
    seg.rt[g] = seg.modify(w, 1, C, seg.rt[g], -1);
  }

  dfs(1);
  for (int i = 1; i <= n; i++) {
    std::cout << ans[i] << "\n";
  }

  return 0;
}