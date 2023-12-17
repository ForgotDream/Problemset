/**
 * @file    P4197 Peaks.cpp
 * @author  ForgotDream
 * @brief   Segmen Tree + Kruskal
 * @date    2023-12-16
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e5 + 50;
int n, m, q, a[N];
struct Edge {
  int u, v, w;
  bool operator<(const Edge &rhs) { return w < rhs.w; }
};
std::vector<Edge> edges;
struct DSU {
  int fa[N];
  DSU() { std::iota(fa, fa + N, 0); }
  int find(int u) { return u == fa[u] ? u : fa[u] = find(fa[u]); }
} dsu;
std::vector<int> adj[N];
int val[N];
int dfn[N], idfn[N], clk, st[20][N], siz[N];
int fa[20][N];
void dfs(int u, int frm) {
  idfn[dfn[u] = ++clk] = u, siz[u] = 1;
  fa[0][u] = frm;
  for (int i = 1; i <= std::__lg(n); i++) fa[i][u] = fa[i - 1][fa[i - 1][u]];
  for (auto v : adj[u]) {
    if (v == frm) continue;
    dfs(v, u), siz[u] += siz[v];
  }
}
inline int in(int u) { return dfn[u]; }
inline int out(int u) { return dfn[u] + siz[u] - 1; }
inline int jump(int u, int x) {
  int cur = u;
  for (int i = std::__lg(n); ~i; i--) {
    if (val[fa[i][cur]] <= x) cur = fa[i][cur];
  }
  return cur;
}
struct SegTree {
  struct Node {
    int lc, rc, sum;
  } tree[N << 6];
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
  int query(int s, int t, int u, int v, int k) {
    if (s == t) return (tree[u].sum - tree[v].sum >= k) * s;
    int mid = (s + t) >> 1, cur = tree[rc(u)].sum - tree[rc(v)].sum;
    if (k <= cur) return query(mid + 1, t, rc(u), rc(v), k);
    else return query(s, mid, lc(u), lc(v), k - cur);
  }
} seg;
int rt[N];
std::vector<int> b;
inline int find(int u) {
  return std::lower_bound(b.begin(), b.end(), u) - b.begin() + 1;
}
void solve() {
  std::cin >> n >> m >> q;
  for (int i = 1; i <= n; i++) std::cin >> a[i], b.push_back(a[i]);
  std::sort(b.begin(), b.end());
  b.erase(std::unique(b.begin(), b.end()), b.end());
  int bn = b.size();
  edges.resize(m);
  for (auto &[u, v, w] : edges) std::cin >> u >> v >> w;
  std::sort(edges.begin(), edges.end());
  int cnt = n;
  val[0] = 2e9;
  for (auto [u, v, w] : edges) {
    int fu = dsu.find(u), fv = dsu.find(v);
    if (fu != fv) {
      cnt++;
      dsu.fa[cnt] = dsu.fa[fu] = dsu.fa[fv] = cnt;
      adj[fu].push_back(cnt), adj[fv].push_back(cnt);
      adj[cnt].push_back(fu), adj[cnt].push_back(fv);
      val[cnt] = w;
    }
    if (cnt == 2 * n - 1) break;
  }
  m = 2 * n - 1;
  dfs(m, 0);
  for (int i = 1; i <= m; i++) {
    if (idfn[i] <= n) seg.modify(find(a[idfn[i]]), 1, bn, rt[i], rt[i - 1]);
    else rt[i] = rt[i - 1];
  }
  for (int v, x, k; q; q--) {
    std::cin >> v >> x >> k;
    int u = jump(v, x);
    int ans = seg.query(1, bn, rt[out(u)], rt[in(u) - 1], k);
    if (!ans) std::cout << -1 << "\n";
    else std::cout << b[ans - 1] << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
