/**
 * @file    P3919 可持久化线段树 1（可持久化数组）.cpp
 * @author  ForgotDream
 * @brief   可持久化线段树
 * @date    2023-03-02
 */
#include <bits/stdc++.h>

using i64 = long long;

struct PersistantSegTree {
  struct Node {
    int l, r, val;
    Node() : l(0), r(0), val(0) {}
    Node operator= (const Node &oth) {
      l = oth.l;
      r = oth.r;
      val = oth.val;
      return (*this);
    }
  };
  int n, cnt;
  std::vector<Node> tree;
  std::vector<int> root, a;

  PersistantSegTree(const int &num) {
    n = num;
    cnt = 0;
    tree.resize(num << 5);
    root.resize(num);
    return;
  }
  PersistantSegTree(const int &num, const std::vector<int> &from) {
    n = num;
    cnt = 0;
    tree.resize(num << 5);
    root.resize(num);
    a = from;
    return;
  }

  int build(int l, int r, int u) {
    u = ++cnt;
    if (l == r) {
      tree[u].val = a[l];
      return u;
    }
    int mid = (l + r) >> 1;
    tree[u].l = build(l, mid, tree[u].l);
    tree[u].r = build(mid + 1, r, tree[u].r);
    return u;
  }

  int modify(int target, int s, int t, int u, int val) {
    int cur = ++cnt;
    tree[cur] = tree[u];
    if (s == t) {
      tree[cur].val = val;
    } else {
      int mid = (s + t) >> 1;
      if (target <= mid) {
        tree[cur].l = modify(target, s, mid, tree[cur].l, val);
      } else {
        tree[cur].r = modify(target, mid + 1, t, tree[cur].r, val);
      }
    }
    return cur;
  }

  int query(int target, int s, int t, int u) {
    if (s == t) {
      return tree[u].val;
    } else {
      int mid = (s + t) >> 1;
      if (target <= mid) {
        return query(target, s, mid, tree[u].l);
      } else {
        return query(target, mid + 1, t, tree[u].r);
      }
    }
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  std::vector<int> a(n + 1);
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i];
  }
  
  PersistantSegTree t(n + 50, a);
  t.root[0] = t.build(1, n, 0);
  // std::cerr << t.root[0] << "\n";
  for (int i = 1; i <= m; i++) {
    int v, opt;
    std::cin >> v >> opt;
    if (opt == 1) {
      int x, y;
      std::cin >> x >> y;
      t.root[i] = t.modify(x, 1, n, t.root[v], y);
      // std::cerr << t.root[i] << "\n";
    } else {
      int x;
      std::cin >> x;
      std::cout << t.query(x, 1, n, t.root[v]) << "\n";
      t.root[i] = t.root[v];
    }
  }

  return 0;
}