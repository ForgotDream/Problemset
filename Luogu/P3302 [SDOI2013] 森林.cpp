/*
 * @file    P3302 [SDOI2013] 森林.cpp
 * @author  ForgotDream
 * @brief   Segmnet Tree + DSU on Tree
 * @date    2023-12-21
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 8e4 + 50;
int n, m, q, a[N];
std::vector<int> adj[N];

std::vector<int> b;
void init() {
  std::sort(b.begin(), b.end());
  b.erase(std::unique(b.begin(), b.end()), b.end());
  m = b.size();
}
inline int find(int u) {
  return std::lower_bound(b.begin(), b.end(), u) - b.begin() + 1;
}

struct SegTree {
  struct Node {
    int lc, rc, siz;
  } tree[N << 9];
  int cnt;
  inline int clone(int u) { return tree[++cnt] = tree[u], cnt; }
  inline int &lc(int u) { return tree[u].lc; }
  inline int &rc(int u) { return tree[u].rc; }
  inline void pushup(int u) { tree[u].siz = tree[lc(u)].siz + tree[rc(u)].siz; }
  void modify(int tar, int s, int t, int &u, int v) {
    u = clone(v);
    if (s == t) return tree[u].siz++, void();
    int mid = (s + t) >> 1;
    if (mid >= tar) modify(tar, s, mid, lc(u), lc(v));
    else modify(tar, mid + 1, t, rc(u), rc(v));
    pushup(u);
  }
  int query(int s, int t, int u, int v, int f, int g, int k) {
    if (s == t) return b[s - 1];
    int mid = (s + t) >> 1;
    int cur = tree[lc(u)].siz + tree[lc(v)].siz - tree[lc(f)].siz - tree[lc(g)].siz;
    if (k <= cur) return query(s, mid, lc(u), lc(v), lc(f), lc(g), k);
    else return query(mid + 1, t, rc(u), rc(v), rc(f), rc(g), k - cur);
  }
} seg;
int rt[N];

struct DSU {
  int fa[N];
  int find(int u) { return u == fa[u] ? u : fa[u] = find(fa[u]); }
} dsu;

int siz[N], fa[20][N], dep[N];
bool vis[N];
void dfs(int u, int frm, int bln) {
  fa[0][u] = frm;
  for (int i = 1; i <= std::__lg(n); i++) fa[i][u] = fa[i - 1][fa[i - 1][u]];
  vis[u] = true, dep[u] = dep[frm] + 1;
  dsu.fa[u] = bln, siz[bln]++;
  seg.modify(find(a[u]), 1, m, rt[u], rt[frm]);
  for (auto v : adj[u]) {
    if (v == frm) continue;
    dfs(v, u, bln);
  }
}
inline int getLCA(int u, int v) {
  if (u == v) return u;
  if (dep[u] < dep[v]) std::swap(u, v);
  // int pu = u, pv = v;
  for (int i = std::__lg(n); ~i; i--) {
    if (dep[fa[i][u]] >= dep[v]) u = fa[i][u];
  }
  // if (pu == 7 && pv == 8) std::cerr << u << " " << v << "\n";
  if (u == v) return u;
  for (int i = std::__lg(n); ~i; i--) {
    if (fa[i][u] != fa[i][v]) u = fa[i][u], v = fa[i][v];
  }
  return fa[0][u];
}

void solve() {
  std::cin >> *(new int);
  std::cin >> n >> m >> q;
  for (int i = 1; i <= n; i++) std::cin >> a[i], b.push_back(a[i]);
  for (int i = 1, u, v; i <= m; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
  }
  init();

  for (int i = 1; i <= n; i++) {
    if (vis[i]) continue;
    dfs(i, 0, i), dsu.fa[i] = i;
  }

  int lst = 0;
  for (int x, y, k; q; q--) {
    char opt[10];
    std::cin >> opt >> x >> y, x ^= lst, y ^= lst;
    if (opt[0] == 'Q') {
      // std::cerr << opt << " " << x << " " << y << "\n";
      std::cin >> k, k ^= lst;
      int lca = getLCA(x, y);
      lst = seg.query(1, m, rt[x], rt[y], rt[lca], rt[fa[0][lca]], k);
      std::cout << lst << "\n";
    } else {
      adj[x].push_back(y), adj[y].push_back(x);
      int fx = dsu.find(x), fy = dsu.find(y);
      if (siz[fx] < siz[fy]) std::swap(fx, fy), std::swap(x, y);
      dfs(y, x, fx);
    }
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // fin >> t;
  while (t--) solve();
  return 0;
}
