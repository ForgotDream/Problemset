/**
 * @file    CF679E Bear and Bad Powers of 42.cpp
 * @author  ForgotDream
 * @brief   Segment Tree
 * @date    2023-06-09
 */
#include <bits/stdc++.h>

using i64 = long long;

namespace FastIO{
  char buf[1 << 23], *p1 = buf, *p2 = buf;
  inline char gc() { return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 23, stdin), p1 == p2) ? EOF : *p1++; }
  template<typename T>
  inline void read(T &x) {
    x = 0;
    T f = 1;
    char c = gc();
    while (!isdigit(c)) { f = (c == '-' ? -f : f), c = gc(); }
    while (isdigit(c)) { x = x * 10 + c - '0', c = gc(); }
    x *= f;
  }
  template<typename T, typename ... args>
  inline void read(T &x, args &...tmp) { read(x), read(tmp...); }
  template<typename T>
  inline void print(T x) {
    if (x < 0) { putchar('-'), x = -x; }
    if (x / 10) { print(x / 10); }
    putchar(x % 10 + '0');
  }
  template<typename T>
  inline void print(T x, char c) { print(x), putchar(c); }
  inline void readString(char *s) {
    char c = gc();
    while (!isdigit(c) && !isalpha(c)) { c = gc(); }
    while (isdigit(c) || isalpha(c)) { *s++ = c, c = gc(); }
  }
}

constexpr std::array<i64, 12> pow42 {
  1, 42, 1764, 
  74088, 3111696, 130691232, 
  5489031744ll, 230539333248ll, 9682651996416ll, 
  406671383849472ll, 17080198121677824ll, 717368321110468608ll
};
int find(i64 num) { 
  return std::lower_bound(pow42.begin(), pow42.end(), num) - pow42.begin(); 
}

struct SegTree {
  int n;
  struct Node { i64 log, add, ass, d; };
  std::vector<Node> tree;
  inline constexpr int lc(int u) { return u << 1; }
  inline constexpr int rc(int u) { return u << 1 | 1; }
  void pushup(int u) { tree[u].d = std::min(tree[lc(u)].d, tree[rc(u)].d); }
  void build(int _n) { n = _n, tree.resize((n << 2) + 1), build(1, n, 1); }
  void build(int s, int t, int u) {
    if (s == t) {
      int val;
      FastIO::read(val), tree[u].log = find(val);
      tree[u].d = pow42[tree[u].log] - val;
      return;
    }
    int mid = (s + t) >> 1;
    build(s, mid, lc(u)), build(mid + 1, t, rc(u));
    pushup(u);
  }
  void tagging(int u, i64 val, int opt) {
    if (opt == 0) {
      (tree[u].ass ? tree[u].ass : tree[u].add) += val;
      tree[u].d -= val;
    } else {
      tree[u].log = find(val), tree[u].d = pow42[tree[u].log] - val;
      tree[u].add = 0, tree[u].ass = val;
    }
  }
  void pushdown(int u) {
    i64 &ass = tree[u].ass, &add = tree[u].add;
    if (ass) { tagging(lc(u), ass, 1), tagging(rc(u), ass, 1), ass = 0; }
    if (add) { tagging(lc(u), add, 0), tagging(rc(u), add, 0), add = 0; }
  }
  void modify(int l, int r, int s, int t, int u, int val) {
    if (l <= s && t <= r) { return tagging(u, val, 0); }
    pushdown(u);
    int mid = (s + t) >> 1;
    if (mid >= l) { modify(l, r, s, mid, lc(u), val); }
    if (mid <  r) { modify(l, r, mid + 1, t, rc(u), val); }
    pushup(u);
  }
  void assign(int l, int r, int s, int t, int u, int val) {
    if (l <= s && t <= r) { return tagging(u, val, 1); }
    pushdown(u);
    int mid = (s + t) >> 1;
    if (mid >= l) { assign(l, r, s, mid, lc(u), val); }
    if (mid <  r) { assign(l, r, mid + 1, t, rc(u), val); }
    pushup(u);
  }
  i64 query(int target, int s, int t, int u) {
    if (s == target && t == target) { return pow42[tree[u].log] - tree[u].d; }
    pushdown(u);
    int mid = (s + t) >> 1;
    if (target <= mid) { 
      return query(target, s, mid, lc(u)); 
    } else { 
      return query(target, mid + 1, t, rc(u)); 
    }
  }
  i64 queryDis(int s, int t, int u) {
    if (tree[u].d >= 0) { return tree[u].d; }
    if (s == t) { 
      i64 val = pow42[tree[u].log] - tree[u].d;
      tree[u].log = find(val), tree[u].d = pow42[tree[u].log] - val;
      return tree[u].d;
    }
    pushdown(u);
    int mid = (s + t) >> 1;
    queryDis(s, mid, lc(u)), queryDis(mid + 1, t, rc(u));
    pushup(u);
    return tree[u].d;
  }
};

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, q;
  FastIO::read(n, q);

  SegTree st;
  st.build(n);

  while (q--) {
    int opt;
    FastIO::read(opt);
    if (opt == 1) {
      int pos;
      FastIO::read(pos);
      FastIO::print(st.query(pos, 1, n, 1), '\n');
    } else if (opt == 2) {
      int l, r, val;
      FastIO::read(l, r, val);
      st.assign(l, r, 1, n, 1, val);
    } else {
      int l, r, val;
      FastIO::read(l, r, val);
      do { st.modify(l, r, 1, n, 1, val); } while (!st.queryDis(1, n, 1));
    }
  }

  return 0;
}