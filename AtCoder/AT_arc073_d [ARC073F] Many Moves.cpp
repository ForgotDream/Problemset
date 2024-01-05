/*
 * @file    AT_arc073_d [ARC073F] Many Moves.cpp
 * @author  ForgotDream
 * @brief   Segment Tree + DP
 * @date    2024-01-05
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e5 + 50;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;
int n, q, A, B;

struct SegTree {
  i64 mn1[N << 2], mn2[N << 2], tag[N << 2];
  SegTree() {
    memset(mn1, 0x3f, sizeof(mn1));
    memset(mn2, 0x3f, sizeof(mn2));
  }
  inline int lc(int u) { return u << 1; }
  inline int rc(int u) { return u << 1 | 1; }
  inline void pushup(int u) { 
    mn1[u] = std::min(mn1[lc(u)], mn1[rc(u)]); 
    mn2[u] = std::min(mn2[lc(u)], mn2[rc(u)]);
  }
  inline void pushdown(int u) {
    if (!tag[u]) return;
    tagging(lc(u), tag[u]), tagging(rc(u), tag[u]);
    tag[u] = 0;
  }
  inline void tagging(int u, i64 val) { 
    mn1[u] += val, mn2[u] += val;
    tag[u] += val; 
  }
  void modify(int tar, int s, int t, int u, i64 val) {
    if (s == t) {
      mn1[u] = std::min(mn1[u], val - s);
      mn2[u] = std::min(mn2[u], val + t);
      return;
    }
    pushdown(u);
    int mid = (s + t) >> 1;
    if (mid >= tar) modify(tar, s, mid, lc(u), val);
    else modify(tar, mid + 1, t, rc(u), val);
    pushup(u);
  }
  i64 query1(int l, int r, int s, int t, int u) {
    if (l <= s && t <= r) return mn1[u];
    pushdown(u);
    int mid = (s + t) >> 1;
    i64 res = inf;
    if (mid >= l) res = std::min(res, query1(l, r, s, mid, lc(u)));
    if (mid < r) res = std::min(res, query1(l, r, mid + 1, t, rc(u)));
    return res;
  }
  i64 query2(int l, int r, int s, int t, int u) {
    if (l <= s && t <= r) return mn2[u];
    pushdown(u);
    int mid = (s + t) >> 1;
    i64 res = inf;
    if (mid >= l) res = std::min(res, query2(l, r, s, mid, lc(u)));
    if (mid < r) res = std::min(res, query2(l, r, mid + 1, t, rc(u)));
    return res;
  }
  i64 traverse(int s, int t, int u) {
    if (s == t) return mn1[u] + s;
    pushdown(u);
    int mid = (s + t) >> 1;
    return std::min(traverse(s, mid, lc(u)), traverse(mid + 1, t, rc(u)));
  }
} seg;

void solve() {
  std::cin >> n >> q >> A >> B;

  seg.modify(B, 1, n, 1, 0);

  for (int i = 1, u, v = A; i <= q; i++, v = u) {
    std::cin >> u;
    i64 val = std::min(seg.query1(1, u, 1, n, 1) + u, 
                       seg.query2(u, n, 1, n, 1) - u);
    // std::cerr << val << "\n";
    seg.tagging(1, std::abs(u - v));
    seg.modify(v, 1, n, 1, val);
  }

  std::cout << seg.traverse(1, n, 1) << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
