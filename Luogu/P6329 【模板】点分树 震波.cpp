/**
 * @file    P6329 【模板】点分树 | 震波.cpp
 * @author  ForgotDream
 * @brief   点分树
 * @date    2023-09-09
 */
#include <iostream>
#include <vector>

using i64 = long long;
using pii = std::pair<int, int>;

constexpr int N = 1e5 + 50;
int n, q, a[N];
std::vector<int> adj[N];
namespace LCA {
int dfn[N], clk, st[21][N], dep[N];
int calc(int x, int y) { return dfn[x] < dfn[y] ? x : y; }
void dfs(int u, int frm) {
  st[0][dfn[u] = ++clk] = frm, dep[u] = dep[frm] + 1;
  for (auto v : adj[u]) {
    if (v == frm) continue;
    dfs(v, u);
  }
}
void init() {
  dfs(1, 0);
  for (int i = 1; i <= std::__lg(n); i++) {
    for (int j = 1; j <= n - (1 << i) + 1; j++) {
      st[i][j] = calc(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
    }
  }
}
int LCA(int u, int v) {
  if (u == v) return u;
  u = dfn[u], v = dfn[v];
  if (u > v) std::swap(u, v);
  int d = std::__lg(v - u++);
  return calc(st[d][u], st[d][v - (1 << d) + 1]);
}
int dis(int u, int v) { return dep[u] + dep[v] - 2 * dep[LCA(u, v)]; }
}  // namespace LCA
namespace DFZ {
int max[N], siz[N], rt, sum;
bool vis[N];
int fa[N];
struct SegTree {
  int cnt = 0, rt[N];
  struct Node {
    int lc = 0, rc = 0, sum = 0;
    Node() = default;
  } tree[N << 6];
  int &lc(int u) { return tree[u].lc; }
  int &rc(int u) { return tree[u].rc; }
  void pushup(int u) { tree[u].sum = tree[lc(u)].sum + tree[rc(u)].sum; }
  void modify(int tar, int s, int t, int &u, int val) {
    if (!u) u = ++cnt;
    if (s == t) return void(tree[u].sum += val);
    int mid = (s + t) >> 1;
    if (mid >= tar) modify(tar, s, mid, lc(u), val);
    else modify(tar, mid + 1, t, rc(u), val);
    pushup(u);
  }
  int query(int l, int r, int s, int t, int u) {
    if (!u) return 0;
    if (l <= s && t <= r) return tree[u].sum;
    int mid = (s + t) >> 1, res = 0;
    if (mid >= l) res += query(l, r, s, mid, lc(u));
    if (mid < r) res += query(l, r, mid + 1, t, rc(u));
    return res;
  }
} dis, ch;
void calcsiz(int u, int frm) {
  siz[u] = 1, max[u] = 0;
  for (auto v : adj[u]) {
    if (v == frm || vis[v]) continue;
    calcsiz(v, u);
    siz[u] += siz[v];
    max[u] = std::max(max[u], siz[v]);
  }
  max[u] = std::max(max[u], sum - siz[u]);
  if (max[u] < max[rt]) rt = u;
}
void dfs(int u, int frm, int st, int d, SegTree &seg) {
  seg.modify(d, 0, n, seg.rt[st], a[u]);
  for (auto v : adj[u]) {
    if (v == frm || vis[v]) continue;
    dfs(v, u, st, d + 1, seg);
  }
}
void dfz(int u) {
  vis[u] = true;
  dfs(u, 0, u, 0, dis);
  for (auto v : adj[u]) {
    if (vis[v]) continue;
    sum = siz[v], rt = 0, max[rt] = 1e9;
    calcsiz(v, u);
    dfs(v, u, rt, 1, ch);
    fa[rt] = u, dfz(rt);
  }
}
void init() {
  sum = n, rt = 0, max[rt] = 1e9;
  calcsiz(1, 0), dfz(rt);
}
void modify(int u, int val) {
  dis.modify(0, 0, n, dis.rt[u], val - a[u]);
  for (int i = u; fa[i]; i = fa[i]) {
    dis.modify(LCA::dis(u, fa[i]), 0, n, dis.rt[fa[i]], val - a[u]);
    ch.modify(LCA::dis(u, fa[i]), 0, n, ch.rt[i], val - a[u]);
  }
  a[u] = val;
}
int query(int u, int val) {
  int res = dis.query(0, val, 0, n, dis.rt[u]);
  for (int i = u; fa[i]; i = fa[i]) {
    res += dis.query(0, val - LCA::dis(u, fa[i]), 0, n, dis.rt[fa[i]]);
    res -= ch.query(0, val - LCA::dis(u, fa[i]), 0, n, ch.rt[i]);
  }
  return res;
}
}  // namespace DFZ
void solve() {
  std::cin >> n >> q;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  for (int i = 1, u, v; i < n; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
  }
  DFZ::init(), LCA::init();
  int lst = 0;
  while (q--) {
    int opt, u, val;
    std::cin >> opt >> u >> val;
    u ^= lst, val ^= lst;
    if (!opt) std::cout << (lst = DFZ::query(u, val)) << "\n";
    else DFZ::modify(u, val);
  }
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}