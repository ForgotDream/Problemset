/*
 * @file    P4482 [BJWC2018] Border 的四种求法.cpp
 * @author  ForgotDream
 * @brief   SAM + HLD + Segment Tree
 * @date    2024-01-13
 */
#include <bits/stdc++.h>

using i64 = long long;
using pii = std::pair<int, int>;

constexpr int N = 4e5 + 50;

int n, m;
char s[N];
std::vector<pii> qry[N];

struct SAM {
  int ch[N][26], len[N], link[N], cnt = 1, lst = 1;
  void expand(char c) {
    int cur = ++cnt, d = c - 'a';
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
    lst = cur;
  }
} sam;

struct HSegTree {
  // 重链直接暴力线段树合并维护吧
  struct Node {
    int lc, rc;
  } tree[N << 5];
  int cnt;
  inline int &lc(int u) { return tree[u].lc; }
  inline int &rc(int u) { return tree[u].rc; }
  void modify(int tar, int s, int t, int &u) {
    if (!u) u = ++cnt;
    if (s == t) return;
    int mid = (s + t) >> 1;
    if (mid >= tar) modify(tar, s, mid, lc(u));
    else modify(tar, mid + 1, t, rc(u));
  }
  int merge(int s, int t, int u, int v) {
    if (!u || !v) return u + v;
    int p = ++cnt;
    if (s == t) return p;
    int mid = (s + t) >> 1;
    lc(p) = merge(s, mid, lc(u), lc(v));
    rc(p) = merge(mid + 1, t, rc(u), rc(v));
    return p;
  }
  int query(int s, int t, int u, int val) {
    if (!u || s > val) return -1;
    if (s == t) return s;
    int mid = (s + t) >> 1;
    int res = query(mid + 1, t, rc(u), val);
    if (res != -1) return res;
    return query(s, mid, lc(u), val);
  }
} hseg;
int rt[N];

struct LSegTree {
  // 这线段树用来维护轻儿子所在子树最大值吧
  int mx[N << 2];
  LSegTree() { memset(mx, -1, sizeof(mx)); }
  inline int lc(int u) { return u << 1; }
  inline int rc(int u) { return u << 1 | 1; }
  void modify(int l, int r, int s, int t, int u, int val) {
    if (l <= s && t <= r) return mx[u] = std::max(mx[u], val), void();
    int mid = (s + t) >> 1;
    if (mid >= l) modify(l, r, s, mid, lc(u), val);
    if (mid < r) modify(l, r, mid + 1, t, rc(u), val);
  }
  void recover(int l, int r, int s, int t, int u) {
    if (l <= s && t <= r) return mx[u] = -1, void();
    int mid = (s + t) >> 1;
    if (mid >= l) recover(l, r, s, mid, lc(u));
    if (mid < r) recover(l, r, mid + 1, t, rc(u));
  }
  int query(int tar, int s, int t, int u) {
    if (s == t) return mx[u];
    int mid = (s + t) >> 1;
    if (mid >= tar) return std::max(mx[u], query(tar, s, mid, lc(u)));
    else return std::max(mx[u], query(tar, mid + 1, t, rc(u)));
  }
} lseg;

std::vector<int> adj[N];
int fa[N], son[N], siz[N], dep[N];
int top[N], dfn[N], idfn[N], clk;

int st[20][N];
std::vector<int> chain[N];

void dfs1(int u) {
  siz[u] = 1, dep[u] = dep[fa[u]] + 1;
  st[0][u] = fa[u];
  for (int i = 1; i <= std::__lg(sam.cnt); i++) st[i][u] = st[i - 1][st[i - 1][u]];
  for (auto v : adj[u]) {
    fa[v] = u, dfs1(v), siz[u] += siz[v];
    if (siz[v] > siz[son[u]]) son[u] = v;
    rt[u] = hseg.merge(1, n, rt[u], rt[v]);
  }
}

void dfs2(int u, int tp) {
  top[u] = tp, dfn[u] = ++clk, idfn[clk] = u;
  chain[tp].push_back(u);
  if (son[u]) dfs2(son[u], tp);
  for (auto v : adj[u]) if (v != son[u]) dfs2(v, v);
}

inline int in(int u) { return dfn[u]; }
inline int out(int u) { return dfn[u] + siz[u] - 1; }

int pos[N], idx[N], ans[N];

void heavy(int u, int l, int r, int id) {
  for (int i = std::__lg(sam.cnt); ~i; i--) {
    if (sam.len[st[i][u]] >= r - l + 1) u = st[i][u];
  }
  u = fa[u];

  while (u) {
    int tmp = hseg.query(1, n, rt[u], l + sam.len[u] - 1);
    if (tmp >= l) ans[id] = std::max(ans[id], tmp - l + 1);
    qry[u].emplace_back(l, id);
    u = fa[top[u]];
  }
}

void light(int tp) {
  for (auto u : chain[tp]) {
    int p = idx[u];
    if (p) lseg.modify(p - sam.len[u] + 1, p, 1, n, 1, p);
    // std::cerr << p << "\n";

    for (auto v : adj[u]) {
      if (v == son[u]) continue;
      for (int j = in(v); j <= out(v); j++) {
        p = idx[idfn[j]];
        if (p) lseg.modify(p - sam.len[u] + 1, p, 1, n, 1, p);
        // std::cerr << p << "\n";
      }
    }

    for (auto [l, id] : qry[u]) {
      ans[id] = std::max(ans[id], lseg.query(l, 1, n, 1) - l + 1);
    }
  }

  for (auto u : chain[tp]) {
    int p = idx[u];
    if (p) lseg.recover(p - sam.len[u] + 1, p, 1, n, 1);

    for (auto v : adj[u]) {
      if (v == son[u]) continue;
      for (int j = in(v); j <= out(v); j++) {
        p = idx[idfn[j]];
        if (p) lseg.recover(p - sam.len[u] + 1, p, 1, n, 1);
      }
    }
  }
}

void solve() {
  std::cin >> (s + 1) >> m;
  n = strlen(s + 1);

  for (int i = 1; i <= n; i++) sam.expand(s[i]), pos[i] = sam.lst;
  for (int i = 1; i <= n; i++) idx[pos[i]] = i, hseg.modify(i, 1, n, rt[pos[i]]);

  for (int i = 2; i <= sam.cnt; i++) adj[sam.link[i]].push_back(i);
  dfs1(1), dfs2(1, 1);

  for (int l, r, i = 1; i <= m; i++) {
    std::cin >> l >> r;
    heavy(pos[r], l, r, i);
  }

  for (int i = 1; i <= sam.cnt; i++) {
    if (top[i] != i) continue;
    light(i);
  }

  for (int i = 1; i <= m; i++) std::cout << ans[i] << "\n";
}

signed main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
