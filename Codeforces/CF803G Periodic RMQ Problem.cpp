/**
 * @file    CF803G Periodic RMQ Problem.cpp
 * @author  ForgotDream
 * @brief   SegTree
 * @date    2023-10-26
 */
#include <cassert>
#include <iostream>

using i64 = long long;

constexpr int N = 1e5 + 50;
int n, k, q, a[N];
struct ST {
  i64 st[20][N];
  void init() {
    for (int i = 1; i <= n; i++) st[0][i] = a[i];
    for (int i = 1; i <= std::__lg(n); i++) {
      for (int j = 1; j <= n - (1 << i) + 1; j++) {
        st[i][j] = std::min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
      }
    }
  }
  i64 query(int l, int r) {
    int d = std::__lg(r - l + 1);
    return std::min(st[d][l], st[d][r - (1 << d) + 1]);
  }
} st;
inline int bln(int u) { return (u - 1) / n + 1; }
inline int reduce(int u) { return (u - 1) % n + 1; }
i64 query(int l, int r) {
  if (r - l + 1 >= n) return st.query(1, n);
  if (bln(l) == bln(r)) return st.query(reduce(l), reduce(r));
  return std::min(st.query(reduce(l), n), st.query(1, reduce(r)));
}
struct SegTree {
  struct Node {
    int lc = 0, rc = 0, l, r;
    i64 mn = 1e18, tag = 1e18;
  } tree[N << 7];
  int cnt;
  int &lc(int u) { return tree[u].lc; }
  int &rc(int u) { return tree[u].rc; }
  int init(int l, int r) {
    ++cnt;
    tree[cnt].l = l, tree[cnt].r = r, tree[cnt].mn = ::query(l, r);
    return cnt;
  }
  void pushup(int u) { 
    int l = tree[u].l, r = tree[u].r, mid = (l + r) >> 1;
    if (!lc(u)) lc(u) = init(l, mid);
    if (!rc(u)) rc(u) = init(mid + 1, r);
    tree[u].mn = std::min(tree[lc(u)].mn, tree[rc(u)].mn);
  }
  void tagging(int u, i64 val) { tree[u].tag = tree[u].mn = val; }
  void pushdown(int u) {
    if (tree[u].tag == 1e18) return;
    int l = tree[u].l, r = tree[u].r, mid = (l + r) >> 1;
    if (!lc(u)) lc(u) = init(l, mid);
    if (!rc(u)) rc(u) = init(mid + 1, r);
    tagging(lc(u), tree[u].tag), tagging(rc(u), tree[u].tag);
    tree[u].tag = 1e18;
  }
  void modify(int l, int r, int s, int t, int &u, i64 val) {
    if (!u) u = init(s, t);
    if (l <= s && t <= r) return tagging(u, val);
    pushdown(u);
    int mid = (s + t) >> 1;
    if (mid >= l) modify(l, r, s, mid, lc(u), val);
    if (mid < r) modify(l, r, mid + 1, t, rc(u), val);
    pushup(u);
  }
  i64 query(int l, int r, int s, int t, int &u) {
    if (!u) u = init(s, t);
    if (l <= s && t <= r) return tree[u].mn;
    pushdown(u);
    int mid = (s + t) >> 1;
    i64 res = 1e18;
    if (mid >= l) res = std::min(res, query(l, r, s, mid, lc(u)));
    if (mid < r) res = std::min(res, query(l, r, mid + 1, t, rc(u)));
    return res;
  }
} seg;
void solve() { 
  std::cin >> n >> k;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  st.init();
  int rt = seg.init(1, n * k);
  std::cin >> q;
  for (int opt, l, r; q; q--) {
    std::cin >> opt >> l >> r;
    i64 val;
    if (opt == 1) {
      std::cin >> val;
      seg.modify(l, r, 1, n * k, rt, val);
    } else {
      std::cout << seg.query(l, r, 1, n * k, rt) << "\n";
    }
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
