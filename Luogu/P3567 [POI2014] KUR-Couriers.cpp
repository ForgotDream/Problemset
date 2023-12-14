/**
 * @file    P3567 [POI2014] KUR-Couriers.cpp
 * @author  ForgotDream
 * @brief   Segment Tree
 * @date    2023-12-14
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 5e5 + 50;
int n, m;
struct SegTree {
  struct Node {
    int lc, rc, sum;
  } tree[N << 5];
  int cnt;
  inline int &lc(int u) { return tree[u].lc; }
  inline int &rc(int u) { return tree[u].rc; }
  inline void pushup(int u) { tree[u].sum = tree[lc(u)].sum + tree[rc(u)].sum; }
  inline int clone(int u) {
    tree[++cnt] = tree[u];
    return cnt;
  }
  void modify(int tar, int s, int t, int &u, int v) {
    u = clone(v);
    if (s == t) return tree[u].sum++, void();
    int mid = (s + t) >> 1;
    if (mid >= tar) modify(tar, s, mid, lc(u), lc(v));
    else modify(tar, mid + 1, t, rc(u), rc(v));
    pushup(u);
  }
  int query(int s, int t, int u, int v, int k) {
    if (s == t) return s;
    int mid = (s + t) >> 1;
    if (2 * (tree[lc(u)].sum - tree[lc(v)].sum) > k) return query(s, mid, lc(u), lc(v), k);
    if (2 * (tree[rc(u)].sum - tree[rc(v)].sum) > k) return query(mid + 1, t, rc(u), rc(v), k);
    return 0;
  }
} seg;
int rt[N];
void solve() {
  std::cin >> n >> m;
  for (int i = 1, x; i <= n; i++) std::cin >> x, seg.modify(x, 1, n, rt[i], rt[i - 1]);
  for (int l, r; m; m--) std::cin >> l >> r, std::cout << seg.query(1, n, rt[r], rt[l - 1], (r - l + 1)) << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
