/**
 * @file    AT_dp_w Intervals.cpp
 * @author  ForgotDream
 * @brief   线段树优化 DP
 * @date    2023-09-08
 */
#include <iostream>
#include <vector>

using i64 = long long;
using pii = std::pair<int, int>;

constexpr int N = 2e5 + 50;
class SegTree {
 private:
  i64 max[N << 2], tag[N << 2];
  int lc(int u) { return u << 1; }
  int rc(int u) { return u << 1 | 1; }
  void pushup(int u) { max[u] = std::max(max[lc(u)], max[rc(u)]); }
  void tagging(int u, i64 val) { tag[u] += val, max[u] += val; }
  void pushdown(int u) {
    if (!tag[u]) return;
    tagging(lc(u), tag[u]), tagging(rc(u), tag[u]);
    tag[u] = 0;
  }
 public:
  void modify(int l, int r, int s, int t, int u, i64 val) {
    if (l <= s && t <= r) return tagging(u, val);
    pushdown(u);
    int mid = (s + t) >> 1;
    if (mid >= l) modify(l, r, s, mid, lc(u), val);
    if (mid < r) modify(l, r, mid + 1, t, rc(u), val);
    pushup(u);
  }
  i64 query() { return std::max(0ll, max[1]); }
} seg;
int n, m;
std::vector<pii> a[N];
void solve() {
  std::cin >> n >> m;
  for (int i = 1, l, r, v; i <= m; i++) {
    std::cin >> l >> r >> v;
    a[r].emplace_back(l, v);
  }
  for (int i = 1; i <= n; i++) {
    seg.modify(i, i, 1, n, 1, seg.query());
    for (auto [l, v] : a[i]) seg.modify(l, i, 1, n, 1, v);
  }
  std::cout << seg.query() << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}