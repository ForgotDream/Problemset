/**
 * @file    P3332 [ZJOI2013] K大数查询.cpp
 * @author  ForgotDream
 * @brief   Segment Tree
 * @date    2023-12-12
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 5e4 + 50;
int n, q;
struct Query {
  int opt, l, r;
  i64 k;
} qry[N];
struct SegTree {
  struct Node {
    int lc, rc, l, r;
    i64 tag, sum;
  } tree[N << 9];
  int cnt;
  inline int &lc(int u) { return tree[u].lc; }
  inline int &rc(int u) { return tree[u].rc; }
  inline void pushup(int u) { tree[u].sum = tree[lc(u)].sum + tree[rc(u)].sum; }
  inline void init(int &u, int l, int r) {
    if (u) return;
    u = ++cnt, tree[u].l = l, tree[u].r = r;
  }
  inline void pushdown(int u) {
    if (!tree[u].tag) return;
    int l = tree[u].l, r = tree[u].r, mid = (l + r) >> 1;
    init(lc(u), l, mid), tagging(lc(u), tree[u].tag);
    init(rc(u), mid + 1, r), tagging(rc(u), tree[u].tag);
    tree[u].tag = 0;
  }
  inline void tagging(int u, i64 val) {
    tree[u].sum += (tree[u].r - tree[u].l + 1) * val;
    tree[u].tag += val;
  }
  void modify(int l, int r, int s, int t, int &u, int val) {
    init(u, s, t);
    if (l <= s && t <= r) return tagging(u, val);
    pushdown(u);
    int mid = (s + t) >> 1;
    if (mid >= l) modify(l, r, s, mid, lc(u), val);
    if (mid < r) modify(l, r, mid + 1, t, rc(u), val);
    pushup(u);
  }
  i64 query(int l, int r, int s, int t, int u) {
    if (!u) return 0;
    if (l <= s && t <= r) return tree[u].sum;
    pushdown(u);
    int mid = (s + t) >> 1;
    i64 res = 0;
    if (mid >= l) res += query(l, r, s, mid, lc(u));
    if (mid < r) res += query(l, r, mid + 1, t, rc(u));
    return res;
  }
} seg;
int rt[N << 2];
std::vector<int> b;
inline int find(int u) {
  return std::lower_bound(b.begin(), b.end(), u) - b.begin() + 1;
}
inline int lc(int u) { return u << 1; }
inline int rc(int u) { return u << 1 | 1; }
void modify(int tar, int s, int t, int u, int l, int r) {
  seg.modify(l, r, 1, n, rt[u], 1);
  if (s == t) return;
  int mid = (s + t) >> 1;
  if (mid >= tar) modify(tar, s, mid, lc(u), l, r);
  else modify(tar, mid + 1, t, rc(u), l, r);
}
int query(int s, int t, int u, i64 k, int l, int r) {
  if (s == t) return b[s - 1];
  int mid = (s + t) >> 1;
  i64 cur = seg.query(l, r, 1, n, rt[rc(u)]);
  if (cur >= k) return query(mid + 1, t, rc(u), k, l, r);
  else return query(s, mid, lc(u), k - cur, l, r);
}
void solve() {
  std::cin >> n >> q;
  for (int i = 1; i <= q; i++) {
    std::cin >> qry[i].opt >> qry[i].l >> qry[i].r >> qry[i].k;
    if (qry[i].opt == 1) b.push_back(qry[i].k);
  }
  std::sort(b.begin(), b.end());
  b.erase(std::unique(b.begin(), b.end()), b.end());
  int m = b.size();
  for (int i = 1; i <= q; i++) {
    auto [opt, l, r, k] = qry[i];
    if (opt == 1) modify(find(k), 1, m, 1, l, r);
    else std::cout << query(1, m, 1, k, l, r) << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
