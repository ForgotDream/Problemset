#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 5e5 + 50;

struct SegTree {
  int mx[N << 2];
  int lc(int u) { return u << 1; }
  int rc(int u) { return u << 1 | 1; }
  void pushup(int u) { mx[u] = std::max(mx[lc(u)], mx[rc(u)]); }
  void modify(int tar, int s, int t, int u, int val) {
    if (s == t) return mx[u] = std::max(mx[u], val), void();
    int mid = (s + t) >> 1;
    if (tar <= mid) modify(tar, s, mid, lc(u), val);
    else modify(tar, mid + 1, t, rc(u), val);
    pushup(u);
  }
  int query(int l, int r, int s, int t, int u) {
    if (l <= s && t <= r) return mx[u];
    int mid = (s + t) >> 1, res = 0;
    if (mid >= l) res = std::max(res, query(l, r, s, mid, lc(u)));
    if (mid < r) res = std::max(res, query(l, r, mid + 1, t, rc(u)));
    return res;
  }
} seg;

int n, d, a[N];

void solve() {
  std::cin >> n >> d;
  int m = 0;
  for (int i = 1; i <= n; i++) std::cin >> a[i], m = std::max(m, a[i]);
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    int lo = std::max(1, a[i] - d), hi = std::min(m, a[i] + d);
    int f = seg.query(lo, hi, 1, m, 1) + 1;
    seg.modify(a[i], 1, m, 1, f);
    ans = std::max(ans, f);
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

