/**
 * @file    P4644 [USACO05DEC] Cleaning Shifts S.cpp
 * @author  ForgotDream
 * @brief   线段树优化 DP
 * @date    2023-10-08
 */
#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

using i64 = long long;

constexpr int N = 1e4 + 50, M = 1e5 + 50;
constexpr i64 inf = 0x3f3f3f3f3f3f3f3f;
int n, m, e;
struct Query {
  int l, r, w;
} q[N];
std::vector<int> b[M];
i64 f[M];
struct SegTree {
  i64 tree[M << 2];
  SegTree() { std::memset(tree, 0x3f, sizeof(tree)); }
  int lc(int u) { return u << 1; }
  int rc(int u) { return u << 1 | 1; }
  void modify(int tar, int s, int t, int u, i64 val) {
    if (s == t) return void(tree[u] = std::min(tree[u], val));
    int mid = (s + t) >> 1;
    if (mid >= tar) modify(tar, s, mid, lc(u), val);
    else modify(tar, mid + 1, t, rc(u), val);
    tree[u] = std::min(tree[lc(u)], tree[rc(u)]);
  }
  i64 query(int l, int r, int s, int t, int u) {
    if (l <= s && t <= r) return tree[u];
    int mid = (s + t) >> 1;
    i64 res = inf;
    if (mid >= l) res = std::min(res, query(l, r, s, mid, lc(u)));
    if (mid < r) res = std::min(res, query(l, r, mid + 1, t, rc(u)));
    return res;
  }
} seg;
void solve() {
  std::cin >> n >> m >> e;
  m++, e++;
  for (int i = 1; i <= n; i++) {
    std::cin >> q[i].l >> q[i].r >> q[i].w;
    q[i].l++, q[i].r++, b[q[i].r].push_back(i);
  }
  std::memset(f, 0x3f, sizeof(f));
  f[m - 1] = 0, seg.modify(m - 1, 0, 1e5, 1, f[m - 1]);
  for (int i = m; i <= e; i++) {
    for (auto j : b[i]) {
      auto [l, r, w] = q[j];
      f[i] = std::min(f[i], seg.query(l - 1, r, 0, 1e5, 1) + w);
    }
    seg.modify(i, 0, 1e5, 1, f[i]);
  }
  // for (int i = m - 1; i <= e; i++) std::cerr << f[i] << " \n"[i == e];
  if (f[e] == inf) std::cout << -1 << "\n";
  else std::cout << f[e] << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
