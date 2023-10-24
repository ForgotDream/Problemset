/**
 * @file    UVA1400 "Ray, Pass me the dishes!".cpp
 * @author  ForgotDream
 * @brief   SegTree + GSS
 * @date    2023-10-11
 */
#include <algorithm>
#include <iostream>
#include <string>

using i64 = long long;

constexpr int N = 5e5 + 50;
int n, m, a[N];
struct SegTree {
  struct Node {
    i64 sum, lmax, rmax, max;
    int lmaxr, rmaxl, maxl, maxr;
    inline Node(int i = 0, int val = 0) {
      sum = lmax = rmax = max = val;
      lmaxr = rmaxl = maxl = maxr = i;
    }
    inline Node operator+(const Node &rhs) const {
      Node res;
      res.sum = sum + rhs.sum;
      res.lmax = std::max(lmax, sum + rhs.lmax);
      res.rmax = std::max(rhs.rmax, rhs.sum + rmax);
      res.max = std::max({max, rhs.max, rmax + rhs.lmax});
      if (res.lmax == lmax) res.lmaxr = lmaxr;
      else res.lmaxr = rhs.lmaxr;
      if (res.rmax == rhs.sum + rmax) res.rmaxl = rmaxl;
      else res.rmaxl = rhs.rmaxl;
      if (res.max == max) res.maxl = maxl, res.maxr = maxr;
      else if (res.max == rmax + rhs.lmax) res.maxl = rmaxl, res.maxr = rhs.lmaxr;
      else res.maxl = rhs.maxl, res.maxr = rhs.maxr;
      return res;
    }
  } tree[N << 2];
  inline int lc(int u) { return u << 1; }
  inline int rc(int u) { return u << 1 | 1; }
  void build(int s, int t, int u) {
    if (s == t) return tree[u] = Node(s, a[s]), void();
    int mid = (s + t) >> 1;
    build(s, mid, lc(u)), build(mid + 1, t, rc(u));
    tree[u] = tree[lc(u)] + tree[rc(u)];
  }
  Node query(int l, int r, int s, int t, int u) {
    if (l <= s && t <= r) return tree[u];
    int mid = (s + t) >> 1;
    if (mid >= r) return query(l, r, s, mid, lc(u));
    else if (mid < l) return query(l, r, mid + 1, t, rc(u));
    else return query(l, r, s, mid, lc(u)) + query(l, r, mid + 1, t, rc(u));
  }
} seg;
void solve() {
  static int d = 0;
  std::cout << "Case " << ++d << ":\n";
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  seg.build(1, n, 1);
  while (m--) {
    int l, r;
    std::cin >> l >> r;
    if (l > r) std::swap(l, r);
    auto res = seg.query(l, r, 1, n, 1);
    std::cout << res.maxl << " " << res.maxr << "\n";
  }
}

int main() {
  // std::freopen("tmp.in", "r", stdin);
  // std::freopen("tmp.out", "w", stdout);
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // fin >> t;
  while (std::cin >> n >> m) solve();
  return 0;
}
