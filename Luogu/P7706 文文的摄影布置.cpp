/**
 * @file    P7706 文文的摄影布置.cpp
 * @author  ForgotDream
 * @brief   Segment Tree
 * @date    2023-05-07
 */
#include <bits/stdc++.h>

using i64 = long long;
using i64u = unsigned long long;
using f80 = long double;

struct SegTree {
  static constexpr int INF = 1e9;
  struct Node {
    int maxPsi, maxA, minB;
    int d1, d2;
    Node() {}
    Node(int _p, int _a, int _b, int _d1, int _d2) 
      : maxPsi(_p), maxA(_a), minB(_b), d1(_d1), d2(_d2) {}
  };
  int n;
  std::vector<Node> tree;
  std::vector<int> a, b;

  SegTree(int _n, const std::vector<int> &_a, const std::vector<int> &_b) {
    n = _n;
    a = _a, b = _b;
    tree.resize(n << 2);
    return;
  }

  Node pushup(const Node &lhs, const Node &rhs) {
    Node res;

    res.maxA = std::max(lhs.maxA, rhs.maxA);
    res.minB = std::min(lhs.minB, rhs.minB);
    res.d1 = std::max({
      lhs.d1, rhs.d1, lhs.maxA - rhs.minB
    });
    res.d2 = std::max({
      lhs.d2, rhs.d2, rhs.maxA - lhs.minB
    });
    res.maxPsi = std::max({
      lhs.maxPsi, rhs.maxPsi, lhs.d1 + rhs.maxA, rhs.d2 + lhs.maxA
    });

    return res;
  }

  void build(int l, int r, int u) {
    if (l == r) {
      tree[u] = Node(-INF, a[l], b[l], -INF, -INF);
      return;
    }
    int mid = (l + r) >> 1, lc = u << 1, rc = u << 1 | 1;
    build(l, mid, lc), build(mid + 1, r, rc);
    tree[u] = pushup(tree[lc], tree[rc]);
    return;
  }

  void modify(int target, int s, int t, int u, int opt, int val) {
    if (target == s && t == target) {
      if (opt == 1) {
        tree[u].maxA = val;
      } else {
        tree[u].minB = val;
      }
      return;
    }
    int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
    if (target <= mid) {
      modify(target, s, mid, lc, opt, val);
    } else {
      modify(target, mid + 1, t, rc, opt, val);
    }
    tree[u] = pushup(tree[lc], tree[rc]);
    return;
  }

  Node query(int l, int r, int s, int t, int u) {
    if (l <= s && t <= r) {
      return tree[u];
    }
    int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
    if (l > mid) {
      return query(l, r, mid + 1, t, rc);
    } else if (r <= mid) {
      return query(l, r, s, mid, lc);
    } else {
      return pushup(query(l, r, s, mid, lc), query(l, r, mid + 1, t, rc));
    } 
  }
};

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  std::vector<int> a(n + 1), b(n + 1);
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i];
  }
  for (int i = 1; i <= n; i++) {
    std::cin >> b[i];
  }

  SegTree t(n + 1, a, b);
  t.build(1, n, 1);

  while (m--) {
    int opt, x, y;
    std::cin >> opt >> x >> y;
    if (opt != 3) {
      t.modify(x, 1, n, 1, opt, y);
    } else {
      std::cout << t.query(x, y, 1, n, 1).maxPsi << "\n";
    }
  }

  return 0;
}