/**
 * @file    P3834 可持久化线段树 2.cpp
 * @author  ForgotDream
 * @brief   可持久化线段树
 * @date    2023-03-02
 */
#include <bits/stdc++.h>

using i64 = long long;

template<int N>
struct SegTree {
  struct Node {
    int l, r, val;
    Node() {
      l = r = val = 0;
      return;
    }
  };
  std::vector<Node> tree;
  std::vector<int> root, a;
  int cnt;

  SegTree() {
    tree.resize(N << 6);
    root.resize(N, 0);
    cnt = 0;
    return;
  }
  SegTree(const std::vector<int> &from) {
    tree.resize(N << 6);
    root.resize(N, 0);
    a = from;
    cnt = 0;
    return;
  }

  int update(int lst, int s, int t, int val) {
    int u = ++cnt;
    tree[u].l = tree[lst].l;
    tree[u].r = tree[lst].r;
    tree[u].val = tree[lst].val + 1;
    int mid = (s + t) >> 1;
    if (s < t) {
      if (val <= mid) {
        tree[u].l = update(tree[lst].l, s, mid, val);
      } else {
        tree[u].r = update(tree[lst].r, mid + 1, t, val);
      }
    }
    return u;
  }

  int query(int l, int r, int s, int t, int k) {
    if (s == t) {
      return s;
    }
    int mid = (s + t) >> 1, val = tree[tree[r].l].val - tree[tree[l].l].val;
    if (val >= k) {
      return query(tree[l].l, tree[r].l, s, mid, k);
    } else {
      return query(tree[l].r, tree[r].r, mid + 1, t, k - val);
    }
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  std::vector<int> a(n + 1, 0);
  SegTree<200050> t;
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i];
  }
  std::vector<int> b(a);

  sort(b.begin() + 1, b.end());
  int cnt = unique(b.begin() + 1, b.end()) - b.begin() - 1;

  for (int i = 1; i <= n; i++) {
    int num = std::lower_bound(b.begin() + 1, b.begin() + cnt + 1, a[i]) - b.begin();
    t.root[i] = t.update(t.root[i - 1], 1, cnt, num);
  }

  while (m--) {
    int x, y, k;
    std::cin >> x >> y >> k;
    int idx = t.query(t.root[x - 1], t.root[y], 1, cnt, k);
    std::cout << b[idx] << "\n";
  }

  return 0;
}