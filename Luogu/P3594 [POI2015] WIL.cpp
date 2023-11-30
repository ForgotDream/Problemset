/**
 * @file    P3594 [POI2015] WIL.cpp
 * @author  ForgotDream
 * @brief   Segment Tree
 * @date    2023-11-28
 */
#include <bits/stdc++.h>

using i64 = int64_t;

constexpr int N = 2e6 + 50;
int n, d;
i64 p, a[N], tmp[N], s[N];
struct SegTree {
  i64 tree[N << 2];
  int lc(int u) { return u << 1; }
  int rc(int u) { return u << 1 | 1; }
  void pushup(int u) { tree[u] = std::max(tree[lc(u)], tree[rc(u)]); }
  void build(int s, int t, int u) {
    if (s == t) return tree[u] = tmp[s], void();
    int mid = (s + t) >> 1;
    build(s, mid, lc(u)), build(mid + 1, t, rc(u));
    pushup(u);
  }
  i64 query(int l, int r, int s, int t, int u) {
    if (l > r) return 0ll;
    if (l <= s && t <= r) return tree[u];
    int mid = (s + t) >> 1;
    i64 res = 0;
    if (mid >= l) res = std::max(res, query(l, r, s, mid, lc(u)));
    if (mid < r) res = std::max(res, query(l, r, mid + 1, t, rc(u)));
    return res;
  }
} seg;
void solve() {
  std::cin >> n >> p >> d;
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i], s[i] = s[i - 1] + a[i];
    if (i >= d) tmp[i - d + 1] = s[i] - s[i - d];
  }
  seg.build(1, n, 1);
  int r = d, ans = 0;
  for (int i = 1; i <= n; i++) {
    while (r <= n && s[r] - s[i - 1] - seg.query(i, r - d + 1, 1, n, 1) <= p) r++;
    ans = std::max(ans, r - i);
  }
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
