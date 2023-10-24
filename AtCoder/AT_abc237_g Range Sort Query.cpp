/**
 * @file    AT_abc237_g Range Sort Query.cpp
 * @author  ForgotDream
 * @brief   Segment Tree
 * @date    2023-06-06
 */
#include <bits/stdc++.h>

using i64 = long long;

struct SegTree {
  int n;
  struct Node { 
    int sum, tag, l, r; 
    Node() { sum = l = r = 0, tag = -1; }
  };
  friend Node operator+(const Node &lhs, const Node &rhs) {
    Node res;
    res.l = lhs.l, res.r = rhs.r, res.sum = lhs.sum + rhs.sum;
    return res;
  }
  std::vector<Node> tree;
  std::vector<int> a;
  SegTree(int _n) { n = _n, tree.resize((n << 2) + 1); }
  void build(int l, int r, int u) {
    if (l == r) {
      tree[u].l = l, tree[u].r = r, tree[u].sum = a[l - 1];
      return;
    }
    int mid = (l + r) >> 1, lc = u << 1, rc = u << 1 | 1;
    build(l, mid, lc), build(mid + 1, r, rc);
    tree[u] = tree[lc] + tree[rc];
  }
  void build(const std::vector<int> &_a) {
    a = _a;
    build(1, n, 1);
  }
  void tagging(int u, int val) {
    tree[u].sum = (tree[u].r - tree[u].l + 1) * val;
    tree[u].tag = val;
  }
  void pushdown(int u) {
    if (tree[u].tag == -1) { return; }
    tagging(u << 1, tree[u].tag), tagging(u << 1 | 1, tree[u].tag);
    tree[u].tag = -1;
  }
  void assign(int l, int r, int u, int val) {
    int s = tree[u].l, t = tree[u].r;
    if (l <= s && t <= r) {
      tagging(u, val);
      return;
    }
    pushdown(u);
    int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
    if (mid >= l) { assign(l, r, lc, val); }
    if (mid <  r) { assign(l, r, rc, val); }
    tree[u] = tree[lc] + tree[rc];
  }
  int query(int l, int r, int u) {
    int s = tree[u].l, t = tree[u].r;
    if (l <= s && t <= r) { return tree[u].sum; }
    pushdown(u);
    int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
    int res = 0;
    if (mid >= l) { res += query(l, r, lc); }
    if (mid <  r) { res += query(l, r, rc); }
    return res;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m, p;
  std::cin >> n >> m >> p;

  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  SegTree t1(n), t2(n);
  std::vector<int> b(n), c(n);
  for (int i = 0; i < n; i++) { b[i] = (a[i] >= p), c[i] = (a[i] > p); }
  t1.build(b), t2.build(c);
  
  for (int i = 0; i < m; i++) {
    int opt, l, r;
    std::cin >> opt >> l >> r;

    int cnt1 = t1.query(l, r, 1), cnt2 = t2.query(l, r, 1);
    t1.assign(l, r, 1, 0), t2.assign(l, r, 1, 0);
    if (opt == 2) {
      if (cnt1) { t1.assign(l, l + cnt1 - 1, 1, 1); }
      if (cnt2) { t2.assign(l, l + cnt2 - 1, 1, 1); }
    } else {
      if (cnt1) { t1.assign(r - cnt1 + 1, r, 1, 1); }
      if (cnt2) { t2.assign(r - cnt2 + 1, r, 1, 1); }
    }
  }

  for (int i = 1; i <= n; i++) {
    if ((!!t1.query(i, i, 1)) && (!t2.query(i, i, 1))) {
      std::cout << i << "\n";
      return 0;
    }
  }

  return 0;
}