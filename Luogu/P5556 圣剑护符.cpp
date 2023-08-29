/**
 * @file    P5556 圣剑护符.cpp
 * @author  ForgotDream
 * @brief   SegTree + Linear Basis
 * @date    2023-08-27
 */
#include <cstring>
#include <iostream>
#include <vector>

using i64 = long long;

constexpr int N = 1e5 + 50;
int n, q, v[N];
std::vector<int> adj[N];
namespace VECSPACE {
constexpr int N = 32;
struct LinearBasis {
  int p[N];
  LinearBasis() { init(); }
  void init() { std::memset(p, 0, sizeof(p)); }
  bool insert(int val) {
    for (int i = 31; ~i; i--) {
      if (!(val & (1ll << i))) continue;
      if (!p[i]) {
        p[i] = val;
        return true;
      }
      val ^= p[i];
    }
    return false;
  }
};
}
namespace HLD {
constexpr int N = ::N;
int siz[N], dep[N], fa[N], son[N];
int dfn[N], idfn[N], clk, top[N];
VECSPACE::LinearBasis lb;
void dfs1(int u, int frm) {
  dep[u] = dep[fa[u] = frm] + 1, siz[u] = 1;
  for (auto v : adj[u]) {
    if (v == frm) continue;
    dfs1(v, u);
    siz[u] += siz[v];
    if (siz[v] > siz[son[u]]) son[u] = v;
  }
}
void dfs2(int u, int rt) {
  top[u] = rt, dfn[u] = ++clk, idfn[clk] = u;
  if (son[u]) dfs2(son[u], rt);
  for (auto v : adj[u]) {
    if (v == fa[u] || v == son[u]) continue;
    dfs2(v, v);
  }
}
struct SegTree {
  int sum[N << 2], tag[N << 2];
  int lc(int u) { return u << 1; }
  int rc(int u) { return u << 1 | 1; }
  void pushup(int u) { sum[u] = sum[lc(u)] ^ sum[rc(u)]; }
  void tagging(int u, int val) { sum[u] ^= val, tag[u] ^= val; }
  void pushdown(int u) {
    if (!tag[u]) return;
    tagging(lc(u), tag[u]), tagging(rc(u), tag[u]);
    tag[u] = 0;
  }
  void build(int s, int t, int u) {
    if (s == t) return void(sum[u] = v[idfn[s]]);
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
  int query(int tar, int s, int t, int u) {
    if (s == t) return sum[u];
    pushdown(u);
    int mid = (s + t) >> 1;
    if (mid >= tar) return query(tar, s, mid, lc(u));
    else return query(tar, mid + 1, t, rc(u));
  }
} seg;
void modifyP2P(int u, int v, int val) {
  while (top[u] != top[v]) {
    if (dep[top[u]] < dep[top[v]]) std::swap(u, v);
    seg.modify(dfn[top[u]], dfn[u], 1, n, 1, val);
    u = fa[top[u]];
  }
  if (dep[u] > dep[v]) std::swap(u, v);
  seg.modify(dfn[u], dfn[v], 1, n, 1, val);
}
int LCA(int u, int v) {
  while (top[u] != top[v]) {
    if (dep[top[u]] < dep[top[v]]) std::swap(u, v);
    u = fa[top[u]];
  }
  return dep[u] < dep[v] ? u : v;
}
bool queryP2P(int u, int v) {
  lb.init();
  int lca= LCA(u, v);
  if (dep[u] + dep[v] - 2 * dep[lca] + 1 > 30) return true;
  if (!lb.insert(seg.query(dfn[lca], 1, n, 1))) return true;
  while (u != lca) {
    if (!lb.insert(seg.query(dfn[u], 1, n, 1))) return true;
    u = fa[u];
  }
  while (v != lca) {
    if (!lb.insert(seg.query(dfn[v], 1, n, 1))) return true;
    v = fa[v];
  }
  return false;
}
}
void solve() {
  std::cin >> n >> q;
  for (int i = 1; i <= n; i++) std::cin >> v[i];
  for (int i = 1, u, v; i < n; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
  }
  HLD::dfs1(1, 0), HLD::dfs2(1, 1);
  HLD::seg.build(1, n, 1);
  while (q--) {
    char opt[10];
    int u, v, x;
    std::cin >> opt >> u >> v;
    if (opt[0] == 'Q') std::cout << (HLD::queryP2P(u, v) ? "YES\n" : "NO\n");
    else std::cin >> x, HLD::modifyP2P(u, v, x);
  }
  // for (int i = 1; i <= n; i++) {
  //   std::cerr << HLD::seg.query(HLD::dfn[i], 1, n, 1) << "\n";
  // }
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}