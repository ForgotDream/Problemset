/**
 * @file    P4560 [IOI2014] Wall 砖墙.cpp
 * @author  ForgotDream
 * @brief   Segment Tree
 * @date    2023-11-27
 */
#include <bits/stdc++.h>

using i64 = int64_t;

constexpr int N = 2e6 + 50;
int n, m;
struct SegTree {
  int mx[N << 2], mn[N << 2];
  int lc(int u) { return u << 1; }
  int rc(int u) { return u << 1 | 1; }
  void pushdown(int u) {
    tagMax(lc(u), mx[u]), tagMax(rc(u), mx[u]);
    tagMin(lc(u), mn[u]), tagMin(rc(u), mn[u]);
    mx[u] = 0, mn[u] = INT_MAX;
  }
  void tagMax(int u, int val) { mx[u] = std::max(mx[u], val), mn[u] = std::max(mn[u], val); }
  void tagMin(int u, int val) { mx[u] = std::min(mx[u], val), mn[u] = std::min(mn[u], val); }
  void modify(int l, int r, int s, int t, int u, int typ, int val) {
    if (l <= s && t <= r) return typ ? tagMin(u, val) : tagMax(u, val);
    pushdown(u);
    int mid = (s + t) >> 1;
    if (mid >= l) modify(l, r, s, mid, lc(u), typ, val);
    if (mid < r) modify(l, r, mid + 1, t, rc(u), typ, val);
  }
  void traverse(int s, int t, int u) {
    if (s == t) return std::cout << mx[u] << "\n", void();
    pushdown(u);
    int mid = (s + t) >> 1;
    traverse(s, mid, lc(u)), traverse(mid + 1, t, rc(u));
  }
} seg;
void solve() {
  std::cin >> n >> m;
  for (int i = 1; i <= (n << 1); i++) seg.mn[i] = INT_MAX;
  for (int typ, l, r, val; m; m--) {
    std::cin >> typ >> l >> r >> val;
    seg.modify(l + 1, r + 1, 1, n, 1, typ - 1, val);
  }
  seg.traverse(1, n, 1);
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
