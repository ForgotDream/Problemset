/**
 * @file    P2839 [国家集训队] middle.cpp
 * @author  ForgotDream
 * @brief   Segment Tree
 * @date    2023-12-15
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e4 + 50;
int n, a[N], q, m, x[4];
struct Info {
  int lmx, rmx, sum;
  void init() { lmx = rmx = -N, sum = 0; }
  friend Info operator+(const Info &lhs, const Info &rhs) {
    Info res;
    res.lmx = std::max(lhs.lmx, lhs.sum + rhs.lmx);
    res.rmx = std::max(lhs.rmx + rhs.sum, rhs.rmx);
    res.sum = lhs.sum + rhs.sum;
    return res;
  }
};
struct SegTree {
  struct Node {
    int lc, rc;
    Info val;
  } tree[N << 5];
  int cnt;
  inline int &lc(int u) { return tree[u].lc; }
  inline int &rc(int u) { return tree[u].rc; }
  inline void pushup(int u) { tree[u].val = tree[lc(u)].val + tree[rc(u)].val; }
  inline int clone(int u) { return tree[++cnt] = tree[u], cnt; }
  void build(int s, int t, int &u) {
    u = ++cnt;
    if (s == t) {
      tree[u].val.lmx = tree[u].val.rmx = tree[u].val.sum = 1;
      return;
    }
    int mid = (s + t) >> 1;
    build(s, mid, lc(u)), build(mid + 1, t, rc(u));
    pushup(u);
  }
  void modify(int tar, int s, int t, int &u, int v) {
    u = clone(v);
    if (s == t) {
      tree[u].val.lmx = tree[u].val.rmx = tree[u].val.sum = -1;
      return;
    }
    int mid = (s + t) >> 1;
    if (mid >= tar) modify(tar, s, mid, lc(u), lc(v));
    else modify(tar, mid + 1, t, rc(u), rc(v));
    pushup(u);
  }
  Info query(int l, int r, int s, int t, int u) {
    if (l <= s && t <= r) return tree[u].val;
    int mid = (s + t) >> 1;
    if (mid >= r) return query(l, r, s, mid, lc(u));
    else if (mid < l) return query(l, r, mid + 1, t, rc(u));
    else return query(l, r, s, mid, lc(u)) + query(l, r, mid + 1, t, rc(u));
  }
} seg;
int rt[N];
std::vector<int> b;
bool check(int u) {
  int res = 0;
  if (x[1] + 1 <= x[2] - 1) res += seg.query(x[1] + 1, x[2] - 1, 1, n, rt[u]).sum;
  res += seg.query(x[0], x[1], 1, n, rt[u]).rmx;
  res += seg.query(x[2], x[3], 1, n, rt[u]).lmx;
  // for (auto i : x) std::cerr << i << " ";
  // std::cerr << "\n" << u << " " << res << "\n";
  return res >= 0;
}
void solve() {
  std::cin >> n, b.resize(n);
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  std::iota(b.begin(), b.end(), 1);
  std::sort(b.begin(), b.end(), [&](int lhs, int rhs) {
    return a[lhs] < a[rhs];
  });
  seg.tree[0].val.init();
  seg.build(1, n, rt[1]);
  for (int i = 2; i <= n; i++) seg.modify(b[i - 2], 1, n, rt[i], rt[i - 1]);
  std::cin >> q;
  int lst = 0;
  for (; q; q--) {
    for (auto &i : x) std::cin >> i, i = (i + lst) % n + 1;
    std::sort(x, x + 4);
    int lo = 1, hi = n, ans = 0;
    while (lo <= hi) {
      int mid = (lo + hi) >> 1;
      if (check(mid)) ans = a[b[mid - 1]], lo = mid + 1;
      else hi = mid - 1;
    }
    std::cout << (lst = ans) << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
