/*
 * @file    P4899 [IOI2018] werewolf 狼人.cpp
 * @author  ForgotDream
 * @brief   Segment Tree + Kruskal
 * @date    2023-12-18
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 4e5 + 50;
int n, m, q;
struct Edge { int u, v, w[2]; };
std::vector<Edge> edges;
struct DSU {
  int fa[N];
  inline void init(int _n) { std::iota(fa + 1, fa + _n + 1, 1); }
  int find(int u) { return u == fa[u] ? u : fa[u] = find(fa[u]); }
} dsu;
struct Kruskal {
  std::vector<int> adj[N];
  int val[N], typ;
  int fa[20][N], in[N], out[N], idfn[N], clk;
  void dfs(int u) {
    if (u <= n) in[u] = ++clk, idfn[clk] = u;
    else in[u] = clk + 1;
    for (int i = 1; i <= std::__lg(m); i++) fa[i][u] = fa[i - 1][fa[i - 1][u]]; 
    for (auto v : adj[u]) fa[0][v] = u, dfs(v);
    out[u] = clk;
  }
  void init(int _typ) {
    typ = _typ;
    if (typ == 0) {
      std::sort(edges.begin(), edges.end(), 
                [](Edge lhs, Edge rhs) { return lhs.w[0] < rhs.w[0]; });
    } else {
      std::sort(edges.begin(), edges.end(), 
                [](Edge lhs, Edge rhs) { return lhs.w[1] > rhs.w[1]; });
    }
    for (int i = 1; i <= n; i++) val[i] = i;
    int cnt = n;
    dsu.init(m);
    for (auto [u, v, w] : edges) {
      int fu = dsu.find(u), fv = dsu.find(v);
      if (fu == fv) continue;
      ++cnt, dsu.fa[fu] = dsu.fa[fv] = dsu.fa[cnt] = cnt;
      adj[cnt].push_back(fu), adj[cnt].push_back(fv), val[cnt] = w[typ];
      if (cnt == 2 * n - 1) break;
    }
    dfs(m);
  }
  inline int jump(int u, int x) {
    for (int i = std::__lg(m); ~i; i--) {
      if (typ == 0 && fa[i][u] && val[fa[i][u]] <= x) u = fa[i][u];
      if (typ == 1 && fa[i][u] && val[fa[i][u]] >= x) u = fa[i][u];
    }
    return u;
  }
} mn, mx;
int p[N];
struct SegTree {
  struct Node {
    int lc, rc, sum;
  } tree[N << 5];
  int cnt;
  inline int &lc(int u) { return tree[u].lc; }
  inline int &rc(int u) { return tree[u].rc; }
  inline void pushup(int u) { tree[u].sum = tree[lc(u)].sum + tree[rc(u)].sum; }
  inline int clone(int u) { return tree[++cnt] = tree[u], cnt; }
  void modify(int tar, int s, int t, int &u, int v) {
    u = clone(v);
    if (s == t) return tree[u].sum++, void();
    int mid = (s + t) >> 1;
    if (mid >= tar) modify(tar, s, mid, lc(u), lc(v));
    else modify(tar, mid + 1, t, rc(u), rc(v));
    pushup(u);
  }
  int query(int l, int r, int s, int t, int u, int v) {
    if (l <= s && t <= r) return tree[u].sum - tree[v].sum;
    int mid = (s + t) >> 1, res = 0;
    if (mid >= l) res += query(l, r, s, mid, lc(u), lc(v));
    if (mid < r) res += query(l, r, mid + 1, t, rc(u), rc(v));
    return res;
  }
} seg;
int rt[N];
void solve() {
  std::cin >> n >> m >> q;
  edges.resize(m), m = 2 * n - 1;
  for (auto &[u, v, w] : edges) {
    std::cin >> u >> v, u++, v++;
    w[0] = std::max(u, v), w[1] = std::min(u, v);
  }
  mn.init(0), mx.init(1);
  for (int i = 1; i <= n; i++) p[mx.idfn[i]] = i;
  for (int i = 1; i <= n; i++) seg.modify(p[mn.idfn[i]], 1, n, rt[i], rt[i - 1]);
  for (int u, v, l, r; q; q--) {
    std::cin >> u >> v >> l >> r;
    u++, v++, l++, r++;
    u = mx.jump(u, l), v = mn.jump(v, r);
    int cur = seg.query(mx.in[u], mx.out[u], 1, n, rt[mn.out[v]], rt[mn.in[v] - 1]);
    // std::cerr << u << " " << v << " " << cur << "\n";
    std::cout << (cur > 0) << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
