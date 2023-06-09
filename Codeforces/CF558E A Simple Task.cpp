/**
 * @file    CF558E A Simple Task.cpp
 * @author  ForgotDream
 * @brief   ODT / Segment Tree
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
  std::vector<Node> tree;
  SegTree(int _n) { n = _n, tree.resize((n << 2) + 1); }
  void pushup(int u) { tree[u].sum = tree[u << 1].sum + tree[u << 1 | 1].sum; }
  void tagging(int u, int val) { 
    tree[u].sum = (tree[u].r - tree[u].l + 1) * val;
    tree[u].tag = val;
  }
  void pushdown(int u) {
    if (tree[u].tag == -1) { return; }
    tagging(u << 1, tree[u].tag), tagging(u << 1 | 1, tree[u].tag);
    tree[u].tag = -1;
  }
  void build(int l, int r, int u) {
    tree[u].l = l, tree[u].r = r;
    if (l == r) { return; }
    int mid = (l + r) >> 1, lc = u << 1, rc = u << 1 | 1;
    build(l, mid, lc), build(mid + 1, r, rc);
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
    pushup(u); 
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

  int n, q;
  std::cin >> n >> q;

  std::string s;
  std::cin >> s;

  std::vector<SegTree> st(26, n);
  for (int i = 0; i < 26; i++) { st[i].build(1, n, 1); }

  for (int i = 0; i < n; i++) {
    int d = s[i] - 'a';
    st[d].assign(i + 1, i + 1, 1, 1);
  }

  while (q--) {
    int l, r, k;
    std::cin >> l >> r >> k;
    if (k == 1) {
      int p = l;
      for (int i = 0; i < 26; i++) {
        int cur = st[i].query(l, r, 1);
        if (!cur) { continue; }
        st[i].assign(l, r, 1, 0);
        st[i].assign(p, p + cur - 1, 1, 1);
        p += cur;
      }
    } else {
      int p = r;
      for (int i = 0; i < 26; i++) {
        int cur = st[i].query(l, r, 1);
        if (!cur) { continue; }
        st[i].assign(l, r, 1, 0);
        st[i].assign(p - cur + 1, p, 1, 1);
        p -= cur;
      }
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < 26; j++) {
      if (st[j].query(i + 1, i + 1, 1)) {
        std::cout << char(j + 'a');
        break;
      }
    }
  }
  std::cout << "\n";

  return 0;
}