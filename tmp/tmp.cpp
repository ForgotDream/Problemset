/*
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2024-02-15
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;
using pii = std::pair<int, int>;

constexpr int N = 1e5 + 50;

int sid, n, k, m;
std::vector<int> adj[N];

struct Atom {
  i64 x, v;
} a[2 * N];
int cnt;

struct Query {
  int opt, x, v;
} qry[N];

namespace HLD {

int siz[N], dep[N], son[N], fa[N];
int top[N], dfn[N], idfn[N], clk;

void dfs1(int u, int frm) {
  siz[u] = 1, dep[u] = dep[frm] + 1, fa[u] = frm;
  for (auto v : adj[u]) {
    if (v == frm) continue;
    dfs1(v, u), siz[u] += siz[v];
    if (siz[v] > siz[son[u]]) son[u] = v;
  }
}

void dfs2(int u, int rt) {
  top[u] = rt, idfn[dfn[u] = ++clk] = u;
  if (son[u]) dfs2(son[u], rt);
  for (auto v : adj[u]) {
    if (v == son[u] || v == fa[u]) continue;
    dfs2(v, v);
  }
}

struct SegTree {
  int mn[N << 2], tag[N << 2];

  int lc(int u) { return u << 1; }
  int rc(int u) { return u << 1 | 1; }

  void pushup(int u) { mn[u] = std::min(mn[lc(u)], mn[rc(u)]); }
  void tagging(int u, int val) { mn[u] += val, tag[u] += val; }
  void pushdown(int u) {
    if (!tag[u]) return;
    tagging(lc(u), tag[u]), tagging(rc(u), tag[u]);
    tag[u] = 0;
  }

  void build(int s, int t, int u) {
    if (s == t) return mn[u] = siz[idfn[s]], void();
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

  i64 query(int l, int r, int s, int t, int u) {
    if (l <= s && t <= r) return mn[u];
    pushdown(u);
    int mid = (s + t) >> 1;
    i64 res = 1e9;
    if (mid >= l) res = std::min(res, query(l, r, s, mid, lc(u)));
    if (mid < r) res = std::min(res, query(l, r, mid + 1, t, rc(u)));
    return res;
  }

  i64 get(int l, int r, int s, int t, int u) {
    if (l <= s && t <= r) {
      if (mn[u] > 0) return 0;
      while (s < t) {
        pushdown(u);
        int mid = (s + t) >> 1;
        if (mn[rc(u)] == 0) s = mid + 1;
        else t = mid;
      }
      return idfn[s];
    }
    pushdown(u);
    int mid = (s + t) >> 1;
    if (mid >= r) {
      return get(l, r, s, mid, lc(u));
    } else if (mid < l) {
      return get(l, r, mid + 1, t, rc(u));
    } else {
      int rp = get(l, r, mid + 1, t, rc(u));
      if (rp) return rp;
      else return get(l, r, s, mid, lc(u));
    }
  }
} seg;

void modify(int u, int val) {
  while (u) {
    seg.modify(dfn[top[u]], dfn[u], 1, n, 1, val);
    u = fa[top[u]];
  }
}

int get(int u) {
  while (u) {
    if (seg.query(dfn[top[u]], dfn[u], 1, n, 1) == 0) {
      return seg.get(dfn[top[u]], dfn[u], 1, n, 1);
    }
    u = fa[top[u]];
  }
  return 0;
}

}  // namespace HLD

namespace IN_TREE {

std::set<pii> s[N];

struct SegTree {
  int idx[N << 2];

  int lc(int u) { return u << 1; }
  int rc(int u) { return u << 1 | 1; }

  void pushup(int u) {
    if (a[idx[lc(u)]].v <= a[idx[rc(u)]].v) idx[u] = idx[lc(u)];
    else idx[u] = idx[rc(u)];
  }

  void modify(int tar, int s, int t, int u, int val) {
    if (s == t) return idx[u] = val, void();
    int mid = (s + t) >> 1;
    if (mid >= tar) modify(tar, s, mid, lc(u), val);
    else modify(tar, mid + 1, t, rc(u), val);
    pushup(u);
  }

  int query(int l, int r, int s, int t, int u) {
    if (l <= s && t <= r) return idx[u];
    int mid = (s + t) >> 1;
    if (mid >= r) {
      return query(l, r, s, mid, lc(u));
    } else if (mid < l) {
      return query(l, r, mid + 1, t, rc(u));
    } else {
      int lp = query(l, r, s, mid, lc(u));
      int rp = query(l, r, mid + 1, t, rc(u));
      if (a[lp].v <= a[rp].v) return lp;
      else return rp;
    }
  }
} seg;

void insert(int idx) {
  int x = a[idx].x;
  s[x].emplace(a[idx].v, idx);
  seg.modify(HLD::dfn[x], 1, n, 1, s[x].begin()->first);
}

void erase(int idx) {
  int x = a[idx].x;
  s[x].erase({a[idx].v, idx});
  if (s[x].empty()) seg.modify(HLD::dfn[x], 1, n, 1, 0);
  else seg.modify(HLD::dfn[x], 1, n, 1, s[x].begin()->first);
}

}  // namespace IN_TREE

inline int lc(int u) { return u << 1; }
inline int rc(int u) { return u << 1 | 1; }

void traverse(int s, int t, int u) {
  if (s == t) {

    return;
  }
  int mid = (s + t) >> 1;
}

constexpr int N = 1e5 + 50;

void solve() {
  std::cin >> sid >> n >> k >> m;
  for (int i = 1, u, v; i < n; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
  }
  for (int i = 1; i <= k; i++) std::cin >> a[i].x >> a[i].v;

  for (int i = 1; i <= m; i++) {
    std::cin >> qry[i].opt;
    if (qry[i].opt == 1) std::cin >> qry[i].x >> qry[i].v;
    else std::cin >> qry[i].v;
  }

  for (int i = 1; i <= n; i++) {
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
