/*
 * @file    P4364 [九省联考 2018] IIIDX.cpp
 * @author  ForgotDream
 * @brief   Segment Tree + Greedy
 * @date    2024-02-18
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;
using f64 = double;

constexpr int N = 5e5 + 50;

int n, a[N];
f64 k;

int cnt[N], siz[N], fa[N], ans[N];

struct SegTree {
  int mn[N << 2], tag[N << 2];

  int lc(int u) { return u << 1; }
  int rc(int u) { return u << 1 | 1; }

  void pushup(int u) { mn[u] = std::min(mn[lc(u)], mn[rc(u)]); }
  void tagging(int u, int val) { mn[u] += val, tag[u] += val; }
  void pushdown(int u) {
    if (!tag[u]) return;
    tagging(lc(u), tag[u]), tagging(rc(u), tag[u]);
    tag[u] = 0;
  }

  void build(int s, int t, int u) {
    if (s == t) return mn[u] = s, void();
    int mid = (s + t) >> 1;
    build(s, mid, lc(u)), build(mid + 1, t, rc(u));
    pushup(u);
  }

  void modify(int l, int r, int s, int t, int u, int val) {
    if (l <= s && t <= r) return tagging(u, val);
    pushdown(u);
    int mid = (s + t) >> 1;
    if (mid >= l) modify(l, r, s, mid, lc(u), val);
    if (mid < r) modify(l, r, mid + 1, t, rc(u), val);
    pushup(u);
  }

  int query(int s, int t, int u, int val) {
    if (s == t) return mn[u] >= val ? s : s + 1;
    pushdown(u);
    int mid = (s + t) >> 1;
    if (val <= mn[rc(u)]) return query(s, mid, lc(u), val);
    else return query(mid + 1, t, rc(u), val);
  }
} seg;

void solve() {
  std::cin >> n >> k;
  for (int i = 1; i <= n; i++) std::cin >> a[i];

  std::sort(a + 1, a + n + 1, std::greater<>());

  for (int i = n - 1; i; i--) {
    if (a[i] == a[i + 1]) cnt[i] = cnt[i + 1] + 1;
    else cnt[i] = 0;
  }
  for (int i = 1; i <= n; i++) fa[i] = i / k, siz[i] = 1;
  for (int i = n; i; i--) siz[fa[i]] += siz[i];

  seg.build(1, n, 1);

  for (int i = 1; i <= n; i++) {
    if (fa[i] && fa[i] != fa[i - 1]) {
      seg.modify(ans[fa[i]], n, 1, n, 1, siz[fa[i]] - 1);
    }
    int p = seg.query(1, n, 1, siz[i]);
    p += cnt[p], cnt[p]++, p -= cnt[p] - 1, ans[i] = p;
    seg.modify(p, n, 1, n, 1, -siz[i]);
  }
  for (int i = 1; i <= n; i++) std::cout << a[ans[i]] << " \n"[i == n];
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
