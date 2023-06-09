/**
 * @file    P4314 CPU 监控.cpp
 * @author  ForgotDream
 * @brief   Segment Tree Beats!
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

struct SegTree {
  int n;
  struct Node { int max, hisMax, addTag, hisAdd, assTag, hisAss; };
  std::vector<Node> tree;
  void pushup(int u) {
    int lc = u << 1, rc = u << 1 | 1;
    tree[u].max = std::max(tree[lc].max, tree[rc].max);
    tree[u].hisMax = std::max(tree[lc].hisMax, tree[rc].hisMax);
  }
  void tagging(int u, int val, int hisVal, int opt) {
    if (opt == 0) {
      tree[u].hisMax = std::max(tree[u].hisMax, tree[u].max + hisVal);
      tree[u].max += val; 
      if (tree[u].assTag == INT_MIN) {
        tree[u].hisAdd = std::max(tree[u].hisAdd, tree[u].addTag + hisVal);
        tree[u].addTag += val;
      } else {
        tree[u].hisAss = std::max(tree[u].hisAss, tree[u].assTag + hisVal);
        tree[u].assTag += val;
      }
    } else {
      tree[u].hisMax = std::max(tree[u].hisMax, hisVal);
      tree[u].max = val;
      tree[u].hisAss = std::max(tree[u].hisAss, hisVal);
      tree[u].assTag = val;
    }
  }
  void pushdown(int u) {
    int lc = u << 1, rc = u << 1 | 1;
    if (tree[u].addTag || tree[u].hisAdd) {
      tagging(lc, tree[u].addTag, tree[u].hisAdd, 0);
      tagging(rc, tree[u].addTag, tree[u].hisAdd, 0);
      tree[u].addTag = tree[u].hisAdd = 0;
    }
    if (tree[u].assTag != INT_MIN || tree[u].hisAss != INT_MIN) {
      tagging(lc, tree[u].assTag, tree[u].hisAss, 1);
      tagging(rc, tree[u].assTag, tree[u].hisAss, 1);
      tree[u].assTag = tree[u].hisAss = INT_MIN;
    }
  }
  void build(int l, int r, int u, const std::vector<int> &a) {
    tree[u].assTag = tree[u].hisAss = INT_MIN;
    tree[u].addTag = tree[u].hisAdd = 0;
    if (l == r) {
      tree[u].max = tree[u].hisMax = a[l - 1];
      return;
    }
    int mid = (l + r) >> 1, lc = u << 1, rc = u << 1 | 1;
    build(l, mid, lc, a), build(mid + 1, r, rc, a);
    pushup(u);
  }
  void build(int _n, const std::vector<int> &a) { 
    n = _n, tree.resize((n << 2) + 1);
    build(1, n, 1, a);
  }
  void modify(int l, int r, int s, int t, int u, int val) {
    if (l <= s && t <= r) { return tagging(u, val, std::max(val, 0), 0); }
    pushdown(u);
    int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
    if (mid >= l) { modify(l, r, s, mid, lc, val); }
    if (mid <  r) { modify(l, r, mid + 1, t, rc, val); }
    pushup(u);
  }
  void assign(int l, int r, int s, int t, int u, int val) {
    if (l <= s && t <= r) { return tagging(u, val, val, 1); }
    pushdown(u);
    int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
    if (mid >= l) { assign(l, r, s, mid, lc, val); }
    if (mid <  r) { assign(l, r, mid + 1, t, rc, val); }
    pushup(u);
  }
  int queryMax(int l, int r, int s, int t, int u) {
    if (l <= s && t <= r) { return tree[u].max; }
    pushdown(u);
    int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
    int res = INT_MIN;
    if (mid >= l) { res = std::max(res, queryMax(l, r, s, mid, lc)); }
    if (mid <  r) { res = std::max(res, queryMax(l, r, mid + 1, t, rc)); }
    return res;
  }
  int queryHisMax(int l, int r, int s, int t, int u) {
    if (l <= s && t <= r) { return tree[u].hisMax; }
    pushdown(u);
    int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
    int res = INT_MIN;
    if (mid >= l) { res = std::max(res, queryHisMax(l, r, s, mid, lc)); }
    if (mid <  r) { res = std::max(res, queryHisMax(l, r, mid + 1, t, rc)); }
    return res;
  }
};

signed main() {
  // std::ios::sync_with_stdio(false);
  // std::cin.tie(nullptr);

  int n;
  FastIO::read(n);

  std::vector<int> a(n);
  for (int i = 0; i < n; i++) { FastIO::read(a[i]); }

  SegTree st;
  st.build(n, a);

  int m;
  FastIO::read(m);
  while (m--) {
    char opt[10];
    int l, r;
    FastIO::readString(opt), FastIO::read(l, r);
    if (opt[0] == 'A') {
      FastIO::print(st.queryHisMax(l, r, 1, n, 1), '\n');
    } else if (opt[0] == 'Q') {
      FastIO::print(st.queryMax(l, r, 1, n, 1), '\n');
    } else if (opt[0] == 'P') {
      int val;
      FastIO::read(val);
      st.modify(l, r, 1, n, 1, val);
    } else {
      int val;
      FastIO::read(val);
      st.assign(l, r, 1, n, 1, val);
    }
  }

  return 0;
}