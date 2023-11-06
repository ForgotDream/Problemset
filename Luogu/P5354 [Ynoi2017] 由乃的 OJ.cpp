/**
 * @file    P5354 [Ynoi2017] 由乃的 OJ.cpp
 * @author  ForgotDream
 * @brief   SegTree
 * @date    2023-11-04
 */
#include <cassert>
#include <iostream>
#include <vector>

using i64 = long long;
using u64 = unsigned long long;

constexpr int N = 1e5 + 50;
int n, q, k, typ[N];
u64 val[N];
std::vector<int> adj[N];
inline u64 calc(u64 u, int idx) {
  if (typ[idx] == 1) return u & val[idx];
  else if (typ[idx] == 2) return u | val[idx];
  else return u ^ val[idx];
}
namespace HLD {
int siz[N], dep[N], fa[N], son[N];
int dfn[N], idfn[N], clk, top[N];
void dfs1(int u, int frm) {
  dep[u] = dep[frm] + 1, siz[u] = 1, fa[u] = frm;
  for (auto v : adj[u]) {
    if (v == frm) continue;
    dfs1(v, u), siz[u] += siz[v];
    if (siz[v] > siz[son[u]]) son[u] = v;
  }
}
void dfs2(int u, int rt) {
  top[u] = rt, dfn[u] = ++clk, idfn[clk] = u;
  if (son[u]) dfs2(son[u], rt);
  for (auto v : adj[u]) {
    if (v == son[u] || v == fa[u]) continue;
    dfs2(v, v);
  }
}
struct SegTree {
  struct Node {
    u64 f0 = 0, f1 = 0, g0 = 0, g1 = 0;
    friend Node operator+(const Node &lhs, const Node &rhs) {
      Node res;
      res.f0 = (lhs.f0 & rhs.f1) | ((~lhs.f0) & rhs.f0);
      res.f1 = (lhs.f1 & rhs.f1) | ((~lhs.f1) & rhs.f0);
      res.g0 = (rhs.g0 & lhs.g1) | ((~rhs.g0) & lhs.g0);
      res.g1 = (rhs.g1 & lhs.g1) | ((~rhs.g1) & lhs.g0);
      return res;
    }
  } tree[N << 2];
  int lc(int u) { return u << 1; }
  int rc(int u) { return u << 1 | 1; }
  void build(int s, int t, int u) {
    if (s == t) {
      tree[u].f0 = tree[u].g0 = calc(0, idfn[s]);
      tree[u].f1 = tree[u].g1 = calc(-1, idfn[s]);
      return;
    }
    int mid = (s + t) >> 1;
    build(s, mid, lc(u)), build(mid + 1, t, rc(u));
    tree[u] = tree[lc(u)] + tree[rc(u)];
  }
  void modify(int tar, int s, int t, int u) {
    if (s == t) {
      tree[u].f0 = tree[u].g0 = calc(0, idfn[s]);
      tree[u].f1 = tree[u].g1 = calc(-1, idfn[s]);
      return;
    }
    int mid = (s + t) >> 1;
    if (mid >= tar) modify(tar, s, mid, lc(u));
    else modify(tar, mid + 1, t, rc(u));
    tree[u] = tree[lc(u)] + tree[rc(u)];
  }
  Node query(int l, int r, int s, int t, int u) {
    if (l <= s && t <= r) return tree[u];
    int mid = (s + t) >> 1;
    if (mid >= r) return query(l, r, s, mid, lc(u));
    else if (mid < l) return query(l, r, mid + 1, t, rc(u));
    else return query(l, r, s, mid, lc(u)) + query(l, r, mid + 1, t, rc(u));
  }
} seg;
SegTree::Node s1[N], s2[N];
SegTree::Node query(int u, int v) {
  int p1 = 0, p2 = 0;
  while (top[u] != top[v]) {
    if (dep[top[u]] >= dep[top[v]]) {
      s1[++p1] = seg.query(dfn[top[u]], dfn[u], 1, n, 1);
      u = fa[top[u]];
    } else {
      s2[++p2] = seg.query(dfn[top[v]], dfn[v], 1, n, 1);
      v = fa[top[v]];
    }
  }
  if (dep[u] > dep[v]) s1[++p1] = seg.query(dfn[v], dfn[u], 1, n, 1);
  else s2[++p2] = seg.query(dfn[u], dfn[v], 1, n, 1);
  for (int i = 1; i <= p1; i++) {
    std::swap(s1[i].f0, s1[i].g0), std::swap(s1[i].f1, s1[i].g1);
  }
  SegTree::Node res;
  if (p1) {
    res = s1[1];
    for (int i = 2; i <= p1; i++) res = res + s1[i];
    if (p2) res = res + s2[p2];
  } else {
    res = s2[p2];
  }
  for (int i = p2 - 1; i >= 1; i--) res = res + s2[i];
  return res;
}
}  // namespace HLD
void solve() {
  std::cin >> n >> q >> k;
  for (int i = 1; i <= n; i++) std::cin >> typ[i] >> val[i];
  for (int i = 1, u, v; i < n; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
  }
  HLD::dfs1(1, 0), HLD::dfs2(1, 1);
  HLD::seg.build(1, n, 1);
  for (int opt, u, v; q; q--) {
    u64 m;
    std::cin >> opt >> u >> v >> m;
    if (opt == 1) {
      auto tmp = HLD::query(u, v);
      u64 f0 = tmp.f0, f1 = tmp.f1, ans = 0;
      for (int i = 63; ~i; i--) {
        if (f0 & (1ull << i)) ans += 1ull << i;
        else if (f1 & (1ull << i) && m >= (1ull << i)) ans += 1ull << i, m -= 1ull << i;
      }
      std::cout << ans << "\n";
    } else {
      typ[u] = v, val[u] = m;
      HLD::seg.modify(HLD::dfn[u], 1, n, 1);
    }
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
