/**
 * @file    P3224 [HNOI2012] 永无乡.cpp
 * @author  ForgotDream
 * @brief   SegTree Merge
 * @date    2023-07-27
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 50;
int n, m, q, rk[N];
struct SegTree {
  struct Node {
    int idx, siz, lc, rc;
  } tree[N << 5];
  int rt[N], cnt;
  int &lc(int u) { return tree[u].lc; }
  int &rc(int u) { return tree[u].rc; }
  void pushup(int u) { tree[u].siz = tree[lc(u)].siz + tree[rc(u)].siz; }
  int modify(int tar, int s, int t, int u, int val) {
    if (!u) u = ++cnt;
    if (s == tar && t == tar) {
      tree[u].siz = 1, tree[u].idx = val;
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
      tree[u].siz += tree[v].siz;
      return u;
    }
    int mid = (s + t) >> 1;
    lc(u) = merge(s, mid, lc(u), lc(v));
    rc(u) = merge(mid + 1, t, rc(u), rc(v));
    pushup(u);
    return u;
  }
  Node query(int rk, int s, int t, int u) {
    int mid = (s + t) >> 1;
    if (s == t) return tree[u];
    else if (tree[lc(u)].siz >= rk) return query(rk, s, mid, lc(u));
    else return query(rk - tree[lc(u)].siz, mid + 1, t, rc(u));
  }
} seg;
struct DSU {
  int fa[N];
  DSU() { std::iota(fa, fa + N, 0); }
  int find(int u) { return u == fa[u] ? u : fa[u] = find(fa[u]); }
  bool merge(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return false;
    fa[u] = v, seg.rt[v] = seg.merge(1, n, seg.rt[v], seg.rt[u]);
    return true;
  }
} dsu;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) 
    std::cin >> rk[i], seg.rt[i] = seg.modify(rk[i], 1, n, seg.rt[i], i);
  while (m--) {
    int u, v;
    std::cin >> u >> v;
    dsu.merge(u, v);
  }

  std::cin >> q;
  while (q--) {
    char opt;
    int u, v;
    std::cin >> opt >> u >> v;
    if (opt == 'B') {
      dsu.merge(u, v);
    } else {
      u = dsu.find(u);
      if (seg.tree[seg.rt[u]].siz < v) std::cout << -1 << "\n";
      else std::cout << seg.query(v, 1, n, seg.rt[u]).idx << "\n";
    }
  }

  return 0;
}