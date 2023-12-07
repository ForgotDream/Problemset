/**
 * @file    P5069 [Ynoi2015] 纵使日薄西山.cpp
 * @author  ForgotDream
 * @brief   Segment Tree
 * @date    2023-12-07
 */
#include <bits/stdc++.h>

using i64 = int64_t;

constexpr int N = 1e5 + 50;
int n, m, a[N];
struct SegTree {
  struct Node {
    int l, r;
    i64 s[4];
    bool lc[4], rc[4];
  } tree[N << 2];
  int lc(int u) { return u << 1; }
  int rc(int u) { return u << 1 | 1; }
  void pushup(int u) {
    int l = tree[u].l, r = tree[u].r, mid = (l + r) >> 1;
    if (tree[lc(u)].rc[0] && tree[rc(u)].lc[0]) {
      if (a[mid] >= a[mid + 1]) {
        tree[u].lc[0] = tree[lc(u)].lc[0], tree[u].rc[0] = tree[rc(u)].rc[1];
        tree[u].s[0] = tree[lc(u)].s[0] + tree[rc(u)].s[1];
      } else {
        tree[u].lc[0] = tree[lc(u)].lc[2], tree[u].rc[0] = tree[rc(u)].rc[0];
        tree[u].s[0] = tree[lc(u)].s[2] + tree[rc(u)].s[0];
      }
    } else {
      tree[u].lc[0] = tree[lc(u)].lc[0], tree[u].rc[0] = tree[rc(u)].rc[0];
      tree[u].s[0] = tree[lc(u)].s[0] + tree[rc(u)].s[0];
    }
    if (tree[lc(u)].rc[1] && tree[rc(u)].lc[0]) {
      if (a[mid] >= a[mid + 1]) {
        tree[u].rc[1] = tree[rc(u)].rc[1];
        tree[u].s[1] = tree[lc(u)].s[1] + tree[rc(u)].s[1];
      } else {
        tree[u].rc[1] = tree[rc(u)].rc[0];
        tree[u].s[1] = tree[lc(u)].s[3] + tree[rc(u)].s[0];
      }
    } else {
      tree[u].rc[1] = tree[rc(u)].rc[0];
      tree[u].s[1] = tree[lc(u)].s[1] + tree[rc(u)].s[0];
    }
    if (tree[lc(u)].rc[0] && tree[rc(u)].lc[2]) {
      if (a[mid] >= a[mid + 1]) {
        tree[u].lc[2] = tree[lc(u)].lc[0];
        tree[u].s[2] = tree[lc(u)].s[0] + tree[rc(u)].s[3];
      } else {
        tree[u].lc[2] = tree[lc(u)].lc[2];
        tree[u].s[2] = tree[lc(u)].s[2] + tree[rc(u)].s[2];
      }
    } else {
      tree[u].lc[2] = tree[lc(u)].lc[0];
      tree[u].s[2] = tree[lc(u)].s[0] + tree[rc(u)].s[2];
    }
    if (tree[lc(u)].rc[1] && tree[rc(u)].lc[2]) {
      if (a[mid] >= a[mid + 1]) tree[u].s[3] = tree[lc(u)].s[1] + tree[rc(u)].s[3];
      else tree[u].s[3] = tree[lc(u)].s[3] + tree[rc(u)].s[2];
    } else {
      tree[u].s[3] = tree[lc(u)].s[1] + tree[rc(u)].s[2];
    }
  }
  void build(int s, int t, int u) {
    tree[u].l = s, tree[u].r = t;
    if (s == t) {
      tree[u].s[0] = a[s];
      tree[u].lc[0] = tree[u].rc[0] = true;
      return;
    }
    int mid = (s + t) >> 1;
    build(s, mid, lc(u)), build(mid + 1, t, rc(u));
    pushup(u);
  }
  void modify(int tar, int s, int t, int u, int val) {
    if (s == t) return tree[u].s[0] = val, void();
    int mid = (s + t) >> 1;
    if (mid >= tar) modify(tar, s, mid, lc(u), val);
    else modify(tar, mid + 1, t, rc(u), val);
    pushup(u);
  }
} seg;
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  seg.build(1, n, 1);
  std::cin >> m;
  for (int x, y; m; m--) {
    std::cin >> x >> y;
    a[x] = y, seg.modify(x, 1, n, 1, y);
    std::cout << seg.tree[1].s[0] << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
