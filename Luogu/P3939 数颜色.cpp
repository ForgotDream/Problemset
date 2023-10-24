/**
 * @file    P3939 数颜色.cpp
 * @author  ForgotDream
 * @brief   动态开点线段树
 * @date    2023-06-05
 */
#include <bits/stdc++.h>

using i64 = long long;

namespace FastIO{
  char buf[1 << 23], *p1 = buf, *p2 = buf;
  inline char gc() {
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 23, stdin), p1 == p2) ? EOF : *p1++;
  }

  template<typename T>
  inline void read(T& x) {
    x = 0;
    T f = 1;
    char c = gc();
    while (!isdigit(c)) {
      if (c == '-') f = -1;
      c = gc();
    }
    while (isdigit(c)) x = x * 10 + c - '0', c = gc();
    x *= f;
    return;
  }

  template<typename T, typename ... args>
  inline void read(T& x, args& ... tmp) {
    read(x);
    read(tmp...);
    return;
  }

  template<typename T>
  inline void print(T x) {
    if (x < 0) putchar('-'), x = -x;
    if (x / 10) print(x / 10);
    putchar(x % 10 + '0');
    return;
  }

  template<typename T>
  inline void print(T x, char c) {
    print(x), putchar(c);
    return;
  }
}

struct SegTree {
  int n;
  struct Node {
    int sum;
    int lc, rc, l, r;
    Node() { sum = lc = rc = l = r = 0; }
  };
  std::vector<Node> tree;
  std::unordered_map<int, int> root;
  std::stack<int> pool;
  std::vector<int> col;

  SegTree(int _n, const std::vector<int> &_col) {
    n = _n, col = _col;
    tree.resize((n << 5) + 1);
    for (int i = n << 5; i; i--) { pool.push(i); }
  }

  void pushup(int u) {
    tree[u].sum = tree[tree[u].lc].sum + tree[tree[u].rc].sum;
  }

  int init(int l, int r) {
    int cur = pool.top();
    tree[cur].l = l, tree[cur].r = r;
    pool.pop();
    return cur;
  }

  void del(int u) {
    pool.push(u);
    Node &cur = tree[u];
    cur.l = cur.r = cur.lc = cur.rc = cur.sum = 0;
  }

  void build() {
    for (int i = 0; i < n; i++) {
      int cur = col[i];
      if (!root.count(cur)) { root[cur] = init(1, n); }
      add(i + 1, root[cur]);
    }
  }

  void add(int target, int &u) {
    int s = tree[u].l, t = tree[u].r;
    if (s == target && t == target) {
      tree[u].sum = 1;
      return;
    }
    int mid = (s + t) >> 1, &lc = tree[u].lc, &rc = tree[u].rc;
    if (target <= mid) {
      if (!lc) { lc = init(s, mid); }
      add(target, lc);
    } else {
      if (!rc) { rc = init(mid + 1, t); }
      add(target, rc);
    }
    pushup(u);
  }

  bool erase(int target, int &u) {
    int s = tree[u].l, t = tree[u].r;
    if (s == target && t == target) {
      del(u);
      return true;
    }
    int mid = (s + t) >> 1, &lc = tree[u].lc, &rc = tree[u].rc;
    if (target <= mid) {
      if (erase(target, lc)) { lc = 0; }
    } else {
      if (erase(target, rc)) { rc = 0; }
    }
    if (!lc && !rc) {
      del(u);
      return true;
    } else {
      pushup(u);
      return false;
    }
  }

  void modify(int target, int val) {
    int pre = col[target - 1];
    if (erase(target, root[pre])) { root.erase(pre); }
    col[target - 1] = val;
    if (!root.count(val)) { root[val] = init(1, n); }
    add(target, root[val]);
  }

  int _query(int l, int r, int u) {
    int s = tree[u].l, t = tree[u].r;
    if (l <= s && t <= r) {
      return tree[u].sum;
    }
    int mid = (s + t) >> 1, lc = tree[u].lc, rc = tree[u].rc;
    int res = 0;
    if (mid >= l && lc) {
      res += _query(l, r, lc);
    }
    if (mid < r && rc) {
      res += _query(l, r, rc);
    }
    return res;
  }

  int query(int l, int r, int col) {
    if (!root.count(col) || !root[col]) { return 0; }
    return _query(l, r, root[col]);
  }
};

int main() {
  // std::ios::sync_with_stdio(false);
  // std::cin.tie(nullptr);

  int n, m;
  FastIO::read(n, m);

  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    FastIO::read(a[i]);
  }

  SegTree st(n, a);
  st.build();

  while (m--) {
    int opt;
    FastIO::read(opt);

    if (opt == 1) {
      int u, v, col;
      FastIO::read(u, v, col);
      FastIO::print(st.query(u, v, col), '\n');
    } else {
      int u;
      FastIO::read(u);
      int uc = st.col[u - 1], vc = st.col[u];
      st.modify(u, vc), st.modify(u + 1, uc);
    }
  }

  return 0;
}
