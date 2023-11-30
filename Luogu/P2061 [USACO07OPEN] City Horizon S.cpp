/**
 * @file    P2061 [USACO07OPEN] City Horizon S.cpp
 * @author  ForgotDream
 * @brief   Segment Tree
 * @date    2023-11-28
 */
#include <bits/stdc++.h>

using i64 = int64_t;

constexpr int N = 4e4 + 50;
int m;
struct SegTree {
  struct Node {
    int lc, rc, mx;
  } tree[N << 6];
  int cnt;
  int &lc(int u) { return tree[u].lc; }
  int &rc(int u) { return tree[u].rc; }
  void tagging(int u, int val) { tree[u].mx = std::max(tree[u].mx, val); }
  void modify(int l, int r, int s, int t, int &u, int val) {
    if (!u) u = ++cnt;
    if (l <= s && t <= r) return tagging(u, val);
    int mid = (s + t) >> 1;
    if (mid >= l) modify(l, r, s, mid, lc(u), val);
    if (mid < r) modify(l, r, mid + 1, t, rc(u), val);
  }
  i64 query(int s, int t, int u, int cur) {
    if (!u) return 1ll * (t - s + 1) * cur;
    if (s == t) return std::max(cur, tree[u].mx);
    int mid = (s + t) >> 1;
    cur = std::max(cur, tree[u].mx);
    return query(s, mid, lc(u), cur) + query(mid + 1, t, rc(u), cur);
  }
} seg;
void solve() {
  std::cin >> m;
  int rt = 0;
  for (int l, r, v; m; m--) {
    std::cin >> l >> r >> v;
    seg.modify(l, r - 1, 1, 1e9, rt, v);
  }
  std::cout << seg.query(1, 1e9, rt, 0) << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
