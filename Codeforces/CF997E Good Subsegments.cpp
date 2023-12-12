/**
 * @file    CF997E Good Subsegments.cpp
 * @author  ForgotDream
 * @brief   Segment Tree + Monotonic Stack
 * @date    2023-12-11
 */
#include <bits/stdc++.h>

using i64 = int64_t;
using pii = std::pair<int, int>;

constexpr int N = 1.2e5 + 50;
int n, a[N], q;
std::vector<pii> qry[N];
i64 ans[N];
struct SegTree {
  int mn[N << 2], mcnt[N << 2], mtag[N << 2], ctag[N << 2];
  i64 cnt[N << 2];
  inline int lc(int u) { return u << 1; }
  inline int rc(int u) { return u << 1 | 1; }
  inline void pushup(int u) {
    mn[u] = std::min(mn[lc(u)], mn[rc(u)]), mcnt[u] = 0;
    if (mn[u] == mn[lc(u)]) mcnt[u] += mcnt[lc(u)];
    if (mn[u] == mn[rc(u)]) mcnt[u] += mcnt[rc(u)];
    cnt[u] = cnt[lc(u)] + cnt[rc(u)];
  }
  inline void pushdown(int u) {
    if (mtag[u]) {
      tagMin(lc(u), mtag[u]), tagMin(rc(u), mtag[u]);
      mtag[u] = 0;
    }
    if (ctag[u]) {
      if (mn[u] == mn[lc(u)]) tagCnt(lc(u), ctag[u]);
      if (mn[u] == mn[rc(u)]) tagCnt(rc(u), ctag[u]);
      ctag[u] = 0;
    }
  }
  inline void tagMin(int u, int val) { mn[u] += val, mtag[u] += val; }
  inline void tagCnt(int u, int val) { cnt[u] += 1ll * mcnt[u] * val, ctag[u] += val; }
  void build(int s, int t, int u) {
    if (s == t) return mn[u] = s, mcnt[u] = 1, void();
    int mid = (s + t) >> 1;
    build(s, mid, lc(u)), build(mid + 1, t, rc(u));
    pushup(u);
  }
  void modify(int l, int r, int s, int t, int u, int val) {
    if (l <= s && t <= r) return tagMin(u, val), void();
    pushdown(u);
    int mid = (s + t) >> 1;
    if (mid >= l) modify(l, r, s, mid, lc(u), val);
    if (mid < r) modify(l, r, mid + 1, t, rc(u), val);
    pushup(u);
  }
  i64 query(int l, int r, int s, int t, int u) {
    if (l <= s && t <= r) return cnt[u];
    pushdown(u);
    i64 res = 0;
    int mid = (s + t) >> 1;
    if (mid >= l) res += query(l, r, s, mid, lc(u));
    if (mid < r) res += query(l, r, mid + 1, t, rc(u));
    return res;
  }
} seg;
int smx[N], tmx, smn[N], tmn;
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  std::cin >> q;
  for (int i = 1, l, r; i <= q; i++) {
    std::cin >> l >> r;
    qry[r].emplace_back(l, i);
  }
  for (int i = 1; i <= n; i++) std::sort(qry[i].begin(), qry[i].end());
  seg.build(1, n, 1);
  for (int i = 1; i <= n; i++) {
    seg.tagMin(1, -1);
    while (tmx && a[i] > a[smx[tmx]]) {
      seg.modify(smx[tmx - 1] + 1, smx[tmx], 1, n, 1, a[i] - a[smx[tmx]]);
      tmx--;
    }
    smx[++tmx] = i;
    while (tmn && a[i] < a[smn[tmn]]) {
      seg.modify(smn[tmn - 1] + 1, smn[tmn], 1, n, 1, a[smn[tmn]] - a[i]);
      tmn--;
    }
    smn[++tmn] = i;
    seg.tagCnt(1, 1);
    for (auto [l, idx] : qry[i]) ans[idx] = seg.query(l, i, 1, n, 1);
  }
  for (int i = 1; i <= q; i++) std::cout << ans[i] << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
