/**
 * @file    CF600E Lomsat gelral.cpp
 * @author  ForgotDream
 * @brief   SegTree Merge
 * @date    2023-07-27
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 50;
int n, col[N];
std::vector<int> adj[N];
i64 ans[N];
struct SegTree {
  struct Node {
    int lc, rc, cnt;
    i64 col;
  } tree[N << 5];
  int cnt = 0, rt[N];
  int &lc(int u) { return tree[u].lc; }
  int &rc(int u) { return tree[u].rc; }
  void pushup(int u) {
    if (tree[lc(u)].cnt > tree[rc(u)].cnt)
      tree[u].cnt = tree[lc(u)].cnt, tree[u].col = tree[lc(u)].col;
    else if (tree[lc(u)].cnt < tree[rc(u)].cnt)
      tree[u].cnt = tree[rc(u)].cnt, tree[u].col = tree[rc(u)].col;
    else
      tree[u].cnt = tree[lc(u)].cnt, tree[u].col = tree[lc(u)].col + tree[rc(u)].col;
  }
  int modify(int tar, int s, int t, int u) {
    if (!u) u = ++cnt;
    if (s == tar && t == tar) {
      tree[u].cnt = 1, tree[u].col = tar;
      return u;
    }
    int mid = (s + t) >> 1;
    if (mid >= tar) lc(u) = modify(tar, s, mid, lc(u));
    else rc(u) = modify(tar, mid + 1, t, rc(u));
    pushup(u);
    return u;
  }
  int merge(int s, int t, int u, int v) {
    if (!u || !v) return u ? u : v;
    if (s == t) {
      tree[u].cnt += tree[v].cnt;
      return u;
    }
    int mid = (s + t) >> 1;
    lc(u) = merge(s, mid, lc(u), lc(v));
    rc(u) = merge(mid + 1, t, rc(u), rc(v));
    pushup(u);
    return u;
  }
} seg;

void dfs(int u, int frm) {
  for (auto v : adj[u]) {
    if (v == frm) continue;
    dfs(v, u);
    seg.rt[u] = seg.merge(1, n, seg.rt[u], seg.rt[v]);
  }
  ans[u] = seg.tree[seg.rt[u]].col;
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n;
  for (int i = 1; i <= n; i++) 
    std::cin >> col[i], seg.rt[i] = seg.modify(col[i], 1, n, seg.rt[i]);
  for (int i = 1, u, v; i < n; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  dfs(1, 0);
  for (int i = 1; i <= n; i++) std::cout << ans[i] << " \n"[i == n];
  
  return 0;
}