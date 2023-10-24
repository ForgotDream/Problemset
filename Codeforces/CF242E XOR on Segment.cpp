/**
 * @file    CF242E XOR on Segment.cpp
 * @author  ForgotDream
 * @brief   Segment Tree
 * @date    2023-05-23
 */
#include <bits/stdc++.h>

using i64 = long long;

struct SegTree {
  int n;
  struct Node {
    int sum, tag;
    int l, r;
    Node (int _s = 0, int _t = 0, int _l = 0, int _r = 0) { 
      sum = _s, tag = _t, l = _l, r = _r; 
    }
    friend Node operator+(Node lhs, Node rhs) {
      Node res;
      res.l = lhs.l, res.r = rhs.r;
      res.sum = lhs.sum + rhs.sum;
      return res;
    }
  };
  std::vector<Node> tree;

  SegTree(int _n) {
    n = _n;
    tree.assign((n << 2) + 1, 0);
    build(1, n, 1);
  }

  void tagging(int u) {
    int l = tree[u].l, r = tree[u].r;
    tree[u].sum = (r - l + 1) - tree[u].sum;
    tree[u].tag ^= 1;
  }

  void pushdown(int u) {
    if (!tree[u].tag) {
      return;
    }
    tagging(u << 1), tagging(u << 1 | 1);
    tree[u].tag ^= 1;
  }

  void modify(int l, int r, int s, int t, int u) {
    if (l <= s && t <= r) {
      tagging(u);
      return;
    }
    pushdown(u);
    int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
    if (l <= mid) {
      modify(l, r, s, mid, lc);
    }
    if (r > mid) {
      modify(l, r, mid + 1, t, rc);
    }
    tree[u] = tree[lc] + tree[rc];
  }

  int query(int l, int r, int s, int t, int u) {
    if (l <= s && t <= r) {
      return tree[u].sum;
    }
    pushdown(u);
    int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
    int res = 0;
    if (l <= mid) {
      res += query(l, r, s, mid, lc);
    }
    if (r > mid) {
      res += query(l, r, mid + 1, t, rc);
    }
    return res;
  }

  void build(int l, int r, int u) {
    tree[u].l = l, tree[u].r = r;
    if (l == r) {
      return;
    }
    int mid = (l + r) >> 1, lc = u << 1, rc = u << 1 | 1;
    build(l, mid, lc), build(mid + 1, r, rc);
  }
};

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  std::vector<SegTree> t(21, SegTree(n));

  for (int i = 1; i <= n; i++) {
    int u;
    std::cin >> u;
    for (int j = 0; j <= 20; j++) {
      if (u & (1 << j)) {
        t[j].modify(i, i, 1, n, 1);
      }
    }
  }

  int m;
  std::cin >> m;

  while (m--) {
    int opt, l, r;
    std::cin >> opt >> l >> r;

    if (opt == 1) {
      i64 ans = 0;
      for (int i = 0; i <= 20; i++) {
        ans += 1ll * t[i].query(l, r, 1, n, 1) * (1 << i);
      }
      std::cout << ans << "\n";
    } else {
      int val;
      std::cin >> val;
      for (int i = 0; i <= 20; i++) {
        if (val & (1 << i)) {
          t[i].modify(l, r, 1, n, 1);
        }
      }
    }
  }

  return 0;
}
