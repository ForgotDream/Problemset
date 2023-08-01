/**
 * @file    CF780G Andryusha and Nervous Barriers.cpp
 * @author  ForgotDream
 * @brief   SegTree
 * @date    2023-08-01
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 50, mod = 1e9 + 7, inf = 2e9;
int h, w, n;
struct Node {
  int u, l, r, s;
  bool operator<(const Node &rhs) const { return u > rhs.u; };
} node[N];
struct SegTree {
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                      std::greater<std::pair<int, int>>>
      q[N];
  int tree[N << 2];
  int lc(int u) { return u << 1; }
  int rc(int u) { return u << 1 | 1; }
  void pushup(int u) { tree[u] = std::min(tree[lc(u)], tree[rc(u)]); }
  void build(int s, int t, int u) {
    if (s == t) {
      tree[u] = h + 1, q[s].emplace(h + 1, 1);
      return;
    }
    int mid = (s + t) >> 1;
    build(s, mid, lc(u)), build(mid + 1, t, rc(u));
    pushup(u);
  }
  void modify(int tar, int s, int t, int u, int h, int v) {
    if (s == t) {
      q[tar].emplace(h, v), tree[u] = q[tar].top().first;
      return;
    }
    int mid = (s + t) >> 1;
    if (mid >= tar) modify(tar, s, mid, lc(u), h, v);
    else modify(tar, mid + 1, t, rc(u), h, v);
    pushup(u);
  }
  int query(int l, int r, int s, int t, int u, int lim) {
    if (tree[u] > lim) return 0;
    int res = 0;
    if (s == t) {
      while (!q[s].empty() && q[s].top().first <= lim) {
        (res += q[s].top().second) %= mod, q[s].pop();
      }
      if (q[s].empty()) tree[u] = inf;
      else tree[u] = q[s].top().first;
      return res;
    }
    int mid = (s + t) >> 1;
    if (mid >= l) (res += query(l, r, s, mid, lc(u), lim)) %= mod;
    if (mid <  r) (res += query(l, r, mid + 1, t, rc(u), lim)) %= mod;
    pushup(u);
    return res;
  }
} seg;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> h >> w >> n;
  for (int i = 1; i <= n; i++) {
    auto &[u, l, r, s] = node[i];
    std::cin >> u >> l >> r >> s;
  }
  std::sort(node + 1, node + n + 1);
  seg.build(1, w, 1);

  for (int i = 1; i <= n; i++) {
    auto [u, l, r, s] = node[i];
    int tmp = seg.query(l, r, 1, w, 1, std::min(h + 1, s + u));
    if (l != 1) seg.modify(l - 1, 1, w, 1, u, tmp * (1 + (r == w)) % mod);
    if (r != w) seg.modify(r + 1, 1, w, 1, u, tmp * (1 + (l == 1)) % mod);
  }
  std::cout << seg.query(1, w, 1, w, 1, inf) << "\n";

  return 0;
}
