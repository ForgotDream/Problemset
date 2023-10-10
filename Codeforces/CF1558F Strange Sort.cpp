/**
 * @file    CF1558F Strange Sort.cpp
 * @author  ForgotDream
 * @brief   SegTree
 * @date    2023-10-10
 */
#include <cstring>
#include <iostream>

using i64 = long long;

constexpr int N = 2e5 + 50;
int n, a[N];
struct SegTree {
  int tree[N << 2], tag[N << 2];
  int lc(int u) { return u << 1; }
  int rc(int u) { return u << 1 | 1; }
  void pushup(int u) { tree[u] = std::max(tree[lc(u)], tree[rc(u)]); }
  void tagging(int u, int val) { tree[u] += val, tag[u] += val; }
  void pushdown(int u) {
    if (!tag[u]) return;
    tagging(lc(u), tag[u]), tagging(rc(u), tag[u]);
    tag[u] = 0;
  }
  void clear(int n) {
    for (int i = 1; i <= n << 2; i++) tag[i] = 0;
  }
  void build(int s, int t, int u) {
    if (s == t) return tree[u] = s - (s & 1), void();
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
  int query(int l, int r, int s, int t, int u) {
    if (l <= s && t <= r) return tree[u];
    pushdown(u);
    int mid = (s + t) >> 1, res = 0;
    if (mid >= l) res = std::max(res, query(l, r, s, mid, lc(u)));
    if (mid < r) res = std::max(res, query(l, r, mid + 1, t, rc(u)));
    return res;
  }
} seg;
int l[N], r[N], pos[N];
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i], pos[a[i]] = i;
  seg.clear(n), seg.build(1, n, 1);
  l[n + 1] = n + 1, r[0] = 0;
  for (int i = 1; i <= n; i++) r[i] = std::max(r[i - 1], pos[i]);
  for (int i = n; i >= 1; i--) l[i] = std::min(l[i + 1], pos[i]);
  int ans = 0;
  for (int i = 1; i < n; i++) {
    int u = pos[i];
    seg.modify(u, u, 1, n, 1, u & 1 ? 1 : -1);
    if (u != 1) seg.modify(1, u - 1, 1, n, 1, 1);
    if (u != n) seg.modify(u + 1, n, 1, n, 1, -1);
    ans = std::max(ans, seg.query(l[i + 1], r[i], 1, n, 1));
  }
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}
