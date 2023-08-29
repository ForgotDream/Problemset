/**
 * @file    CF609E Minimum spanning tree for each edge.cpp
 * @author  ForgotDream
 * @brief   SegTree + Kruskal
 * @date    2023-08-26
 */
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

namespace FastIO {
char buf[1 << 23], *p1 = buf, *p2 = buf;
inline char gc() {
  if (p1 == p2) p1 = buf, p2 = buf + fread(buf, 1, 1 << 23, stdin);
  return p1 == p2 ? EOF : *p1++;
}
template <typename T> inline void read(T &x) {
  x = 0;
  T f = 1;
  char c = gc();
  while (!isdigit(c)) f = (c == '-' ? -f : f), c = gc();
  while (isdigit(c)) x = x * 10 + c - '0', c = gc();
  x *= f;
}
template <typename T, typename... args> inline void read(T &x, args &...tmp) {
  read(x), read(tmp...);
}
template <typename T> inline void print(T x) {
  if (x < 0) putchar('-'), x = -x;
  if (x / 10) print(x / 10);
  putchar(x % 10 + '0');
}
template <typename T> inline void print(T x, char c) { print(x), putchar(c); }
inline void readString(char *s) {
  char c = gc();
  while (!isdigit(c) && !isalpha(c)) c = gc();
  while (isdigit(c) || isalpha(c)) *s++ = c, c = gc();
}
} // namespace FastIO

using i64 = long long;
using pii = std::pair<int, int>;

constexpr int N = 2e5 + 50;
int n, m;
std::vector<pii> adj[N];
namespace DSU {
struct DSU {
  int fa[N];
  DSU() { std::iota(fa, fa + N, 0); }
  int find(int u) { return u == fa[u] ? u : fa[u] = find(fa[u]); }
  bool merge(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return false;
    fa[u] = v;
    return true;
  }
} dsu;
}  // namespace DSU
namespace MST {
struct Edge {
  int u, v, w, idx;
  bool operator<(const Edge &rhs) const { return w < rhs.w; }
} edges[N];
bool mark[N];
i64 kruskal() {
  std::sort(edges + 1, edges + m + 1);
  int cnt = 0;
  i64 res = 0;
  for (int i = 1; i <= m; i++) {
    auto [u, v, w, _] = edges[i];
    if (DSU::dsu.merge(u, v)) {
      cnt++, res += w, mark[i] = true;
      adj[u].emplace_back(v, w);
      adj[v].emplace_back(u, w);
      if (cnt == n - 1) break;
    }
  }
  return res;
}
}  // namespace MST
namespace HLD {
int dep[N], siz[N], fa[N], son[N], top[N];
int dfn[N], clk, idfn[N], val[N];
void dfs1(int u, int frm) {
  dep[u] = dep[frm] + 1, siz[u] = 1, fa[u] = frm;
  for (auto [v, w] : adj[u]) {
    if (v == frm) continue;
    val[v] = w;
    dfs1(v, u);
    siz[u] += siz[v];
    if (siz[v] > siz[son[u]]) son[u] = v;
  }
}
void dfs2(int u, int rt) {
  top[u] = rt, dfn[u] = ++clk, idfn[clk] = u;
  if (son[u]) dfs2(son[u], rt);
  for (auto [v, _] : adj[u]) {
    if (v == fa[u] || v == son[u]) continue;
    dfs2(v, v);
  }
}
struct SegTree {
  int tree[N << 2];
  int lc(int u) { return u << 1; }
  int rc(int u) { return u << 1 | 1; }
  void pushup(int u) { tree[u] = std::max(tree[lc(u)], tree[rc(u)]); }
  void build(int s, int t, int u) {
    if (s == t) return void(tree[u] = val[idfn[s]]);
    int mid = (s + t) >> 1;
    build(s, mid, lc(u)), build(mid + 1, t, rc(u));
    pushup(u);
  }
  int query(int l, int r, int s, int t, int u) {
    if (l <= s && t <= r) return tree[u];
    int mid = (s + t) >> 1, res = 0;
    if (mid >= l) res = std::max(res, query(l, r, s, mid, lc(u)));
    if (mid < r) res = std::max(res, query(l, r, mid + 1, t, rc(u)));
    return res;
  }
} seg;
int queryP2P(int u, int v) {
  int res = 0;
  while (top[u] != top[v]) {
    if (dep[top[u]] < dep[top[v]]) std::swap(u, v);
    res = std::max(res, seg.query(dfn[top[u]], dfn[u], 1, n, 1));
    u = fa[top[u]];
  }
  if (dep[u] > dep[v]) std::swap(u, v);
  res = std::max(res, seg.query(dfn[u] + 1, dfn[v], 1, n, 1));
  return res;
}
}  // namespace HLD
i64 ans[N];
void solve() {
  FastIO::read(n, m);
  for (int i = 1; i <= m; i++) {
    FastIO::read(MST::edges[i].u, MST::edges[i].v, MST::edges[i].w);
    MST::edges[i].idx = i;
  }
  auto mst = MST::kruskal();
  HLD::dfs1(1, 0), HLD::dfs2(1, 1);
  HLD::seg.build(1, n, 1);
  for (int i = 1; i <= m; i++) {
    auto [u, v, w, idx] = MST::edges[i];
    if (MST::mark[i]) {
      ans[idx] = mst;
      continue;
    }
    auto max = HLD::queryP2P(u, v);
    ans[idx] = mst - max + w;
  }
  for (int i = 1; i <= m; i++) FastIO::print(ans[i], '\n');
}

int main() {
  // std::ios_base::sync_with_stdio(0);
  // std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}