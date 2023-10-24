/**
 * @file    CF992E Nastya and King-Shamans.cpp
 * @author  ForgotDream
 * @brief   SegTree
 * @date    2023-08-06
 */
#include <bits/stdc++.h>
using i64 = long long;
constexpr int N = 2e5 + 50;
int n, q;
i64 a[N], sum[N];
template<int N = 200050>
struct SegTree {
  i64 max[N << 2], tag[N << 2];
  int lc(int u) { return u << 1; }
  int rc(int u) { return u << 1 | 1; }
  void pushup(int u) { max[u] = std::max(max[lc(u)], max[rc(u)]); }
  void tagging(int u, i64 val) { max[u] += val, tag[u] += val; }
  void pushdown(int u) {
    if (!tag[u]) return;
    tagging(lc(u), tag[u]), tagging(rc(u), tag[u]);
    tag[u] = 0;
  }
  void build(int s, int t, int u) {
    if (s == t) return void(max[u] = a[s] - sum[s - 1]);
    int mid = (s + t) >> 1;
    build(s, mid, lc(u)), build(mid + 1, t, rc(u));
    pushup(u);
  }
  void modify(int l, int r, int s, int t, int u, i64 val) {
    if (l <= s && t <= r) return tagging(u, val);
    pushdown(u);
    int mid = (s + t) >> 1;
    if (mid >= l) modify(l, r, s, mid, lc(u), val);
    if (mid <  r) modify(l, r, mid + 1, t, rc(u), val);
    pushup(u);
  }
  int res = -1;
  void query(int s, int t, int u) {
    if (res != -1) return;
    if (s == t) {
      if (max[u] == 0) res = s;
      return;
    }
    pushdown(u);
    int mid = (s + t) >> 1;
    if (max[lc(u)] >= 0) query(s, mid, lc(u));
    if (max[rc(u)] >= 0) query(mid + 1, t, rc(u));
  }
};
SegTree seg;
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n >> q;
  for (int i = 1; i <= n; i++) std::cin >> a[i], sum[i] = sum[i - 1] + a[i];
  seg.build(1, n, 1);
  while (q--) {
    int idx;
    i64 val;
    std::cin >> idx >> val;
    val = val - a[idx];
    seg.modify(idx, idx, 1, n, 1, val);
    if (idx != n) seg.modify(idx + 1, n, 1, n, 1, -val);
    a[idx] += val;
    seg.res = -1, seg.query(1, n, 1);
    std::cout << seg.res << "\n";
  }
  return 0;
}