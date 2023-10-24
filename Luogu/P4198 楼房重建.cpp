/**
 * @file    P4198 楼房重建.cpp
 * @author  ForgotDream
 * @brief   SegTree
 * @date    2023-10-20
 */
#include <iostream>

using i64 = long long;

constexpr int N = 1e5 + 50;
int n, m, x;
double slope[N], y;
struct SegTree {
  struct Node {
    double max;
    int ans;
  } tree[N << 2];
  int lc(int u) { return u << 1; }
  int rc(int u) { return u << 1 | 1; }
  void pushup(int u) { tree[u].max = std::max(tree[lc(u)].max, tree[rc(u)].max); }
  int pushup(double cur, int s, int t, int u) {
    if (s == t) return slope[s] > cur;
    int mid = (s + t) >> 1;
    if (tree[lc(u)].max <= cur) return pushup(cur, mid + 1, t, rc(u));
    else return pushup(cur, s, mid, lc(u)) + tree[u].ans - tree[lc(u)].ans;
  }
  void modify(int tar, int s, int t, int u, double val) {
    if (s == t) return tree[u].max = val, tree[u].ans = 1, void();
    int mid = (s + t) >> 1;
    if (mid >= tar) modify(tar, s, mid, lc(u), val);
    else modify(tar, mid + 1, t, rc(u), val);
    pushup(u);
    tree[u].ans = tree[lc(u)].ans + pushup(tree[lc(u)].max, mid + 1, t, rc(u));
  }
} seg;
void solve() {
  std::cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    std::cin >> x >> y;
    slope[x] = y / x, seg.modify(x, 1, n, 1, slope[x]);
    std::cout << seg.tree[1].ans << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
