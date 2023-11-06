/**
 * @file    P5607 [Ynoi2013] 无力回天 NOI2017.cpp
 * @author  ForgotDream
 * @brief   SegTree + Linear Basis
 * @date    2023-11-05
 */
#include <cstring>
#include <iostream>

using i64 = long long;

constexpr int N = 5e4 + 50;
int n, m, a[N];
struct LinearBasis {
  static constexpr int N = 30;
  int p[N];
  LinearBasis() { clear(); }
  void clear() { memset(p, 0, sizeof(p)); }
  void insert(int val) {
    for (int i = 29; ~i; i--) {
      if (!(val & (1 << i))) continue;
      if (!p[i]) {
        p[i] = val;
        break;
      }
      val ^= p[i];
    }
  }
  int queryMax(int val) {
    int res = val;
    for (int i = 29; ~i; i--) res = std::max(res, res ^ p[i]);
    return res;
  }
  friend LinearBasis operator+(const LinearBasis &lhs, const LinearBasis &rhs) {
    LinearBasis res = lhs;
    for (int i = 29; ~i; i--) {
      if (rhs.p[i]) res.insert(rhs.p[i]);
    }
    return res;
  }
};
struct SegTree {
  LinearBasis tree[N << 2];
  int lc(int u) { return u << 1; }
  int rc(int u) { return u << 1 | 1; }
  void build(int s, int t, int u) {
    if (s == t) return tree[u].insert(a[s]);
    int mid = (s + t) >> 1;
    build(s, mid, lc(u)), build(mid + 1, t, rc(u));
    tree[u] = tree[lc(u)] + tree[rc(u)];
  }
  void modify(int tar, int s, int t, int u, int val) {
    if (s == t) return tree[u].clear(), tree[u].insert(a[s] ^= val);
    int mid = (s + t) >> 1;
    if (mid >= tar) modify(tar, s, mid, lc(u), val);
    else modify(tar, mid + 1, t, rc(u), val);
    tree[u] = tree[lc(u)] + tree[rc(u)];
  }
  LinearBasis query(int l, int r, int s, int t, int u) {
    if (l <= s && t <= r) return tree[u];
    int mid = (s + t) >> 1;
    if (mid >= r) return query(l, r, s, mid, lc(u));
    else if (mid < l) return query(l, r, mid + 1, t, rc(u));
    return query(l, r, s, mid, lc(u)) + query(l, r, mid + 1, t, rc(u));
  }
} seg;
struct BIT {
  int tree[N];
  void modify(int u, int val) {
    for (int i = u; i <= n; i += i & -i) tree[i] ^= val;
  }
  int query(int u) {
    int res = 0;
    for (int i = u; i; i -= i & -i) res ^= tree[i];
    return res;
  }
} bit;
void solve() {
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  for (int i = n; i >= 2; i--) a[i] = a[i] ^ a[i - 1];
  for (int i = 1; i <= n; i++) bit.modify(i, a[i]);
  seg.build(1, n, 1);
  for (int opt, l, r, v; m; m--) {
    std::cin >> opt >> l >> r >> v;
    if (opt == 1) {
      bit.modify(l, v), seg.modify(l, 1, n, 1, v);
      if (r >= n) continue;
      bit.modify(r + 1, v), seg.modify(r + 1, 1, n, 1, v);
    } else {
      int cur = bit.query(l);
      if (l == r) {
        std::cout << std::max(v, cur ^ v) << "\n";
        continue;
      }
      auto lb = seg.query(l + 1, r, 1, n, 1);
      lb.insert(cur);
      std::cout << lb.queryMax(v) << "\n";
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
