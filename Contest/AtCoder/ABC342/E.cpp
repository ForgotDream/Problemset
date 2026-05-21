#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 2e5 + 50;

int n, a[N], q;

struct SegTree {
  struct Node {
    int lc, rc, mx;
  } tree[N << 8];
  int cnt;

  int &lc(int u) { return tree[u].lc; }
  int &rc(int u) { return tree[u].rc; }

  void pushup(int u) {
    tree[u].mx = std::max(tree[lc(u)].mx, tree[rc(u)].mx);
  }

  void modify(int l, int r, int s, int t, int &u, int val) {
    if (!u) u = ++cnt;
    if (l <= s && t <= r) {
      tree[u].mx = std::max(tree[u].mx, val);
      return;
    }
    int mid = (s + t) >> 1;
    if (mid >= l) modify(l, r, s, mid, lc(u), val);
    if (mid < r) modify(l, r, mid + 1, t, rc(u), val);
    // pushup(u);
  }

  int query(int tar, int s, int t, int u) {
    if (!u) return 0;
    if (s == t) return tree[u].mx;
    int mid = (s + t) >> 1, res = tree[u].mx;
    if (mid >= tar) res = std::max(res, query(tar, s, mid, lc(u)));
    else res = std::max(res, query(tar, mid + 1, t, rc(u)));
    return res;
  }
} seg;
int rt[N << 2];

int lc(int u) { return u << 1; }
int rc(int u) { return u << 1 | 1; }

void modify(int l, int r, int s, int t, int u, int x, int y, int val) {
  if (l <= s && t <= r) return seg.modify(x, y, 1, n, rt[u], val);
  int mid = (s + t) >> 1;
  if (mid >= l) modify(l, r, s, mid, lc(u), x, y, val);
  if (mid < r) modify(l, r, mid + 1, t, rc(u), x, y, val);
}

int query(int tar, int s, int t, int u, int x) {
  if (s == t) return seg.query(x, 1, n, rt[u]);
  int mid = (s + t) >> 1, res = seg.query(x, 1, n, rt[u]);
  if (mid >= tar) res = std::max(res, query(tar, s, mid, lc(u), x));
  else res = std::max(res, query(tar, mid + 1, t, rc(u), x));
  return res;
}

struct Event {
  int opt, l, r, v;
  bool flg;
} e[N];

void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i];

  std::cin >> q;
  for (int i = 1; i <= q; i++) {
    auto &[opt, l, r, v, flg] = e[i];
    std::cin >> opt;
    if (opt == 1) {
      std::cin >> l >> r >> v;
    } else if (opt == 2) {
      std::cin >> v;
      modify(v, i - 1, 0, q, 1, e[v].l, e[v].r, e[v].v);
      e[v].flg = true;
    } else {
      std::cin >> v;
    }
  }

  for (int i = 1; i <= n; i++) modify(0, q, 0, q, 1, i, i, a[i]);
  for (int i = 1; i <= q; i++) {
    if (e[i].opt == 1 && !e[i].flg) {
      modify(i, q, 0, q, 1, e[i].l, e[i].r, e[i].v);
    }
  }

  for (int i = 1; i <= q; i++) {
    if (e[i].opt == 3) {
      std::cout << query(i, 0, q, 1, e[i].v) << "\n";
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
