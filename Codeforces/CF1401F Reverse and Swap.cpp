/**
 * @file    CF1401F Reverse and Swap.cpp
 * @author  ForgotDream
 * @brief   SegTree
 * @date    2023-08-07
 */
#include <bits/stdc++.h>
using i64 = long long;
constexpr int N = 1e6 + 50;
int n, q, a[N];
struct SegTree {
  struct Node {
    int lc = 0, rc = 0, dep = 0;
    i64 sum = 0;
  } tree[N << 2];
  bool swp[20];
  SegTree() { std::memset(swp, 0, sizeof(swp)); }
  int &lc(int u) { return swp[tree[u].dep] ? tree[u].rc : tree[u].lc; }
  int &rc(int u) { return swp[tree[u].dep] ? tree[u].lc : tree[u].rc; }
  void pushup(int u) { tree[u].sum = tree[lc(u)].sum + tree[rc(u)].sum; }
  int cnt = 0, rt = 0;
  int build(int s, int t, int u) {
    if (!u) u = ++cnt;
    if (s == t) {
      tree[u].sum = a[s], tree[u].dep = 0;
      return u;
    }
    int mid = (s + t) >> 1;
    lc(u) = build(s, mid, lc(u));
    rc(u) = build(mid + 1, t, rc(u));
    pushup(u), tree[u].dep = tree[lc(u)].dep + 1;
    return u;
  }
  void swap(int k) { swp[k + 1] ^= 1; }
  void reverse(int k) {
    for (int i = 1; i <= k; i++) swp[i] ^= 1;
  }
  void modify(int tar, int s, int t, int u, int val) {
    if (s == t) return void(tree[u].sum = val);
    int mid = (s + t) >> 1;
    if (mid >= tar) modify(tar, s, mid, lc(u), val);
    else modify(tar, mid + 1, t, rc(u), val);
    pushup(u);
  }
  i64 query(int l, int r, int s, int t, int u) {
    if (l <= s && t <= r) return tree[u].sum;
    int mid = (s + t) >> 1;
    i64 res = 0;
    if (mid >= l) res += query(l, r, s, mid, lc(u));
    if (mid <  r) res += query(l, r, mid + 1, t, rc(u));
    return res;
  }
} seg;
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n >> q;
  int m = 1 << n;
  for (int i = 1; i <= m; i++) std::cin >> a[i];
  seg.build(1, m, seg.rt);
  while (q--) {
    int opt, u, k, l, r;
    std::cin >> opt;
    if (opt == 1) std::cin >> u >> k, seg.modify(u, 1, m, 1, k);
    else if (opt == 2) std::cin >> k, seg.reverse(k);
    else if (opt == 3) std::cin >> k, seg.swap(k);
    else std::cin >> l >> r, std::cout << seg.query(l, r, 1, m, 1) << "\n";
  }
  return 0;
}