/**
 * @file    P3293 [SCOI2016] 美味.cpp
 * @author  ForgotDream
 * @brief   Segment Tree
 * @date    2023-12-15
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e5 + 50;
int n, q, m, a[N];
struct SegTree {
  struct Node {
    int lc, rc, sum;
  } tree[N << 5];
  int cnt;
  inline int &lc(int u) { return tree[u].lc; }
  inline int &rc(int u) { return tree[u].rc; }
  inline void pushup(int u) { tree[u].sum = tree[lc(u)].sum + tree[rc(u)].sum; }
  inline int clone(int u) { return tree[++cnt] = tree[u], cnt; }
  void modify(int tar, int s, int t, int &u, int v) {
    u = clone(v);
    if (s == t) return tree[u].sum++, void();
    int mid = (s + t) >> 1;
    if (mid >= tar) modify(tar, s, mid, lc(u), lc(v));
    else modify(tar, mid + 1, t, rc(u), rc(v));
    pushup(u);
  }
  int query(int l, int r, int s, int t, int u, int v) {
    if (l > r || t < l || s > r) return 0;
    if (l <= s && t <= r) return tree[u].sum - tree[v].sum;
    int mid = (s + t) >> 1, res = 0;
    if (mid >= l) res += query(l, r, s, mid, lc(u), lc(v));
    if (mid < r) res += query(l, r, mid + 1, t, rc(u), rc(v));
    return res;
  }
} seg;
int rt[N];
inline int pw(int u) { return (1 << u); }
inline int mask(int u) { return pw(u) - 1; }

void solve() {
  std::cin >> n >> q;
  for (int i = 1; i <= n; i++) std::cin >> a[i], m = std::max(m, a[i]);
  for (int i = 1; i <= n; i++) seg.modify(a[i], 0, m, rt[i], rt[i - 1]);
  for (int b, x, l, r, ans; q; q--) {
    std::cin >> b >> x >> l >> r, ans = 0;
    for (int i = 17; ~i; i--) {
      int lo, hi;
      if (b & (1 << i)) {
        lo = std::max(0, ans - x), hi = std::min(m, ans - x + mask(i));
        if (!seg.query(lo, hi, 0, m, rt[r], rt[l - 1])) ans += pw(i);
      } else {
        lo = std::max(0, ans - x + pw(i)), hi = std::min(m, ans - x + mask(i + 1));
        if (seg.query(lo, hi, 0, m, rt[r], rt[l - 1])) ans += pw(i);
      }
    }
    std::cout << (ans ^ b) << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
