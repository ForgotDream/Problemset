/**
 * @file    AT_dp_q Flowers.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-06-20
 */
#include <bits/stdc++.h>

using i64 = long long;

struct SegTree {
  int n;
  std::vector<i64> tree;
  SegTree(int _n) { n = _n, tree.resize((n << 2) + 1); }
  void build(int s, int t, int u) {
    if (s == t) {
      tree[u] = -1;
      return;
    }
    int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
    build(s, mid, lc), build(mid + 1, t, rc);
    tree[u] = std::max(tree[lc], tree[rc]);
  }
  void modify(int target, int s, int t, int u, i64 val) {
    if (target == s && target == t) {
      tree[u] = val;
      return;
    }
    int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
    if (target <= mid) {
      modify(target, s, mid, lc, val);
    } else {
      modify(target, mid + 1, t, rc, val);
    }
    tree[u] = std::max(tree[lc], tree[rc]);
  }
  i64 query(int l, int r, int s, int t, int u) {
    if (l <= s && t <= r) { return tree[u]; }
    int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
    i64 res = INT_MIN;
    if (mid >= l) { res = std::max(res, query(l, r, s, mid, lc)); }
    if (mid <  r) { res = std::max(res, query(l, r, mid + 1, t, rc)); }
    return res;
  }
};

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  std::vector<int> h(n), a(n);
  for (int i = 0; i < n; i++) { std::cin >> h[i]; }
  for (int i = 0; i < n; i++) { std::cin >> a[i]; }

  std::vector<i64> f(n);
  SegTree st(n);
  st.build(1, n, 1), f[0] = a[0];
  st.modify(h[0], 1, n, 1, f[0]);
  for (int i = 1; i < n; i++) {
    i64 pre = st.query(1, h[i], 1, n, 1);
    f[i] = (pre == -1 ? 0 : pre) + a[i];
    st.modify(h[i], 1, n, 1, f[i]);
  }

  std::cout << *std::max_element(f.begin(), f.end()) << "\n";

  return 0;
}
