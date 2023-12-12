/**
 * @file    CF1904E Tree Queries.cpp
 * @author  ForgotDream
 * @brief   Segment Tree
 * @date    2023-12-10
 */
#include <bits/stdc++.h>

using i64 = int64_t;
using pii = std::pair<int, int>;

constexpr int N = 2e5 + 50;
int n, q;
std::vector<int> adj[N];
std::vector<std::pair<int, std::vector<int>>> a[N];
int dfn[N], idfn[N], siz[N], clk, dep[N];
struct SegTree {
  int mx[N << 2], tag[N << 2];
  int lc(int u) { return u << 1; }
  int rc(int u) { return u << 1 | 1; }
  void pushup(int u) { mx[u] = std::max(mx[lc(u)], mx[rc(u)]); }
  void pushdown(int u) {
    if (!tag[u]) return;
    tagging(lc(u), tag[u]), tagging(rc(u), tag[u]);
    tag[u] = 0;
  }
  void tagging(int u, int val) { mx[u] += val, tag[u] += val; }
  void build(int s, int t, int u) {
    if (s == t) return mx[u] = dep[idfn[s]], void();
    int mid = (s + t) >> 1;
    build(s, mid, lc(u)), build(mid + 1, t, rc(u));
    pushup(u);
  }
  void modify(int l, int r, int s, int t, int u, int val) {
    if (l > r) return;
    if (l <= s && t <= r) return tagging(u, val);
    pushdown(u);
    int mid = (s + t) >> 1;
    if (mid >= l) modify(l, r, s, mid, lc(u), val);
    if (mid < r) modify(l, r, mid + 1, t, rc(u), val);
    pushup(u);
  }
  int query(int l, int r, int s, int t, int u) {
    if (l > r) return -1e9;
    if (l <= s && t <= r) return mx[u];
    pushdown(u);
    int mid = (s + t) >> 1, res = -1e9;
    if (mid >= l) res = std::max(res, query(l, r, s, mid, lc(u)));
    if (mid < r) res = std::max(res, query(l, r, mid + 1, t, rc(u)));
    return res;
  }
} seg;
void pre(int u, int frm) {
  dfn[u] = ++clk, idfn[clk] = u;
  siz[u] = 1, dep[u] = dep[frm] + 1;
  for (auto v : adj[u]) {
    if (v == frm) continue;
    pre(v, u), siz[u] += siz[v];
  }
}
inline int in(int u) { return dfn[u]; }
inline int out(int u) { return dfn[u] + siz[u] - 1; }
int nxt[N], ans[N];
void dfs(int u, int frm) {
  for (auto &[idx, v] : a[u]) {
    std::vector<pii> del;
    if (std::find(v.begin(), v.end(), u) != v.end()) return;
    for (auto i : v) {
      if (in(i) <= in(u) && out(u) <= out(i)) {
        del.emplace_back(1, in(nxt[i]) - 1);
        del.emplace_back(out(nxt[i]) + 1, n);
      } else {
        del.emplace_back(in(i), out(i));
      }
    }
    std::sort(del.begin(), del.end());
    int p = 1;
    for (auto [l, r] : del) {
      ans[idx] = std::max(ans[idx], seg.query(p, l - 1, 1, n, 1));
      p = std::max(p, r + 1);
    }
    if (p <= n) ans[idx] = std::max(ans[idx], seg.query(p, n, 1, n, 1));
  }
  seg.modify(1, n, 1, n, 1, 1);
  for (auto v : adj[u]) {
    if (v == frm) continue;
    seg.modify(in(v), out(v), 1, n, 1, -2);
    nxt[u] = v, dfs(v, u);
    seg.modify(in(v), out(v), 1, n, 1, 2);
  }
  seg.modify(1, n, 1, n, 1, -1);
}
void solve() {
  std::cin >> n >> q;
  for (int i = 1, u, v; i < n; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
  }
  pre(1, 0), seg.build(1, n, 1);
  for (int i = 1, x, k; i <= q; i++) {
    std::cin >> x >> k;
    std::vector<int> v(k);
    for (auto &j : v) std::cin >> j;
    a[x].emplace_back(i, v);
  }
  dfs(1, 0);
  for (int i = 1; i <= q; i++) std::cout << ans[i] - 1 << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
