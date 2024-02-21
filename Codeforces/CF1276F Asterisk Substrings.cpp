/*
 * @file    CF1276F Asterisk Substrings.cpp
 * @author  ForgotDream
 * @brief   SAM + Segment Tree
 * @date    2024-02-20
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 2e5 + 50;

struct SAM {
  int ch[N][26], len[N], link[N], lst = 1, cnt = 1;
  int pos[N];
  std::vector<int> adj[N];

  int expand(int d) {
    int cur = ++cnt;
    len[cur] = len[lst] + 1;
    int p = lst;
    for (; p && !ch[p][d]; p = link[p]) ch[p][d] = cur;
    if (!p) {
      link[cur] = 1;
    } else {
      int q = ch[p][d];
      if (len[p] + 1 == len[q]) {
        link[cur] = q;
      } else {
        int tmp = ++cnt;
        len[tmp] = len[p] + 1, link[tmp] = link[q];
        memcpy(ch[tmp], ch[q], sizeof(ch[tmp]));
        for (; p && ch[p][d] == q; p = link[p]) ch[p][d] = tmp;
        link[cur] = link[q] = tmp;
      }
    }
    return lst = cur;
  }

  void build() {
    for (int i = 2; i <= cnt; i++) adj[link[i]].push_back(i);
  }
} sam, rev;

int st[20][N], dfn[N], idfn[N], clk;

void init_lca(int u, int frm = 0) {
  st[0][dfn[u] = ++clk] = frm, idfn[clk] = u;
  for (auto v : rev.adj[u]) init_lca(v, u);
}

inline int cmp(int u, int v) { return dfn[u] < dfn[v] ? u : v; }

void init() {
  init_lca(1);
  int m = rev.cnt;
  for (int i = 1; i <= std::__lg(m); i++) {
    for (int j = 1; j <= m - (1 << i) + 1; j++) {
      st[i][j] = cmp(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
    }
  }
}

inline int get_lca(int u, int v) {
  if (u == v) return idfn[u];
  if (u > v) std::swap(u, v);
  int d = std::__lg(v - u++);
  return cmp(st[d][u], st[d][v - (1 << d) + 1]);
}

struct SegTree {
  struct Node {
    int lc, rc, lp, rp;
    i64 sum;
  } tree[N << 5];
  int cnt;

  int &lc(int u) { return tree[u].lc; }
  int &rc(int u) { return tree[u].rc; }
  int &lp(int u) { return tree[u].lp; }
  int &rp(int u) { return tree[u].rp; }

  void pushup(int u) {
    lp(u) = lp(lc(u)) ? lp(lc(u)) : lp(rc(u));
    rp(u) = rp(rc(u)) ? rp(rc(u)) : rp(lc(u));
    tree[u].sum = tree[lc(u)].sum + tree[rc(u)].sum -
                  rev.len[get_lca(rp(lc(u)), lp(rc(u)))];
  }

  void modify(int tar, int s, int t, int &u) {
    if (!u) u = ++cnt;
    if (s == t) {
      tree[u].lp = tree[u].rp = tar;
      tree[u].sum = rev.len[idfn[tar]];
      return;
    }
    int mid = (s + t) >> 1;
    if (mid >= tar) modify(tar, s, mid, lc(u));
    else modify(tar, mid + 1, t, rc(u));
    pushup(u);
  }

  int merge(int s, int t, int u, int v) {
    if (!u || !v) return u + v;
    int mid = (s + t) >> 1, p = ++cnt;
    lc(p) = merge(s, mid, lc(u), lc(v));
    rc(p) = merge(mid + 1, t, rc(u), rc(v));
    pushup(p);
    return p;
  }
} seg;
int rt[N];

int n;
char s[N];

void dfs(int u) {
  for (auto v : sam.adj[u]) {
    dfs(v), rt[u] = seg.merge(1, clk, rt[u], rt[v]);
  }
}

i64 ans;

void solve() {
  std::cin >> (s + 1), n = strlen(s + 1);
  ans = 2;
  for (int i = 1, p; i <= n; i++) {
    sam.pos[i] = p = sam.expand(s[i] - 'a');
    ans += sam.len[p] - sam.len[sam.link[p]];
    if (i < n) ans += sam.len[p] - sam.len[sam.link[p]];
  }
  for (int i = n, p; i >= 1; i--) {
    rev.pos[i] = p = rev.expand(s[i] - 'a');
    if (i > 1) ans += rev.len[p] - rev.len[rev.link[p]];
  }
  sam.build(), rev.build();

  init();
  for (int i = 1; i <= n - 2; i++) {
    seg.modify(dfn[rev.pos[i + 2]], 1, clk, rt[sam.pos[i]]);
    // std::cerr << rt[sam.pos[i]] << " " << dfn[rev.pos[i + 2]] << "\n";
  }
  dfs(1);

  for (int i = 2; i <= sam.cnt; i++) {
    ans += (sam.len[i] - sam.len[sam.link[i]]) * seg.tree[rt[i]].sum;
    std::cerr << seg.tree[rt[i]].sum << "\n";
  }
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
