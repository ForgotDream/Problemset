/**
 * @file    P5787 二分图 /【模板】线段树分治.cpp
 * @author  ForgotDream
 * @brief   SegTree
 * @date    2023-10-26
 */
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using i64 = long long;
using pii = std::pair<int, int>;

constexpr int N = 1e5 + 50;
int n, m, k;
struct DSU {
  int fa[2 * N], siz[2 * N], st[2 * N], top;
  DSU() {
    std::iota(fa, fa + 2 * N, 0);
    std::fill(siz, siz + 2 * N, 1);
  }
  int find(int u) { return u == fa[u] ? u : find(fa[u]); }
  bool merge(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return false;
    if (siz[u] > siz[v]) std::swap(u, v);
    fa[u] = v, siz[v] += siz[u], st[++top] = u;
    return true;
  }
  void undo() {
    if (!top) return;
    int u = st[top--];
    siz[fa[u]] -= siz[u], fa[u] = u;
  }
  void rollback(int cnt) {
    while (top > cnt) undo();
  }
} dsu;
std::vector<pii> edges;
std::vector<int> adj[N << 2];
int lc(int u) { return u << 1; }
int rc(int u) { return u << 1 | 1; }
void modify(int l, int r, int s, int t, int u, int val) {
  if (l <= s && t <= r) return adj[u].push_back(val), void();
  int mid = (s + t) >> 1;
  if (mid >= l) modify(l, r, s, mid, lc(u), val);
  if (mid < r) modify(l, r, mid + 1, t, rc(u), val);
}
void solve(int s, int t, int u) {
  int cur = dsu.top;
  bool flg = true;
  for (auto idx : adj[u]) {
    auto [u, v] = edges[idx];
    if (dsu.find(u) == dsu.find(v)) {
      flg = false;
      for (int i = s; i <= t; i++) std::cout << "No\n";
      break;
    }
    dsu.merge(u, v + n), dsu.merge(v, u + n);
  }
  if (flg) {
    if (s == t) {
      std::cout << "Yes\n";
    } else {
      int mid = (s + t) >> 1;
      solve(s, mid, lc(u)), solve(mid + 1, t, rc(u));
    }
  }
  dsu.rollback(cur);
}
void solve() {
  std::cin >> n >> m >> k;
  edges.resize(m + 1);
  for (int i = 1, u, v, l, r; i <= m; i++) {
    std::cin >> u >> v >> l >> r;
    edges[i] = std::make_pair(u, v);
    modify(l + 1, r, 1, k, 1, i);
  }
  solve(1, k, 1);
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
