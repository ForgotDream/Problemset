/*
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2024-02-16
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;
using pii = std::pair<int, int>;

constexpr int N = 1e5 + 50;

int sid, n, k, m;
std::vector<int> adj[N];

struct Atom {
  int x, v;
} a[2 * N];
int L[2 * N], R[2 * N];

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

inline int in(int u) { return dfn[u]; }
inline int out(int u) { return dfn[u] + siz[u] - 1; }

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
        if (mn[rc(u)] == 0) u = rc(u), s = mid + 1;
        else u = lc(u), t = mid;
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

void init() {
  dfs1(1, 0), dfs2(1, 1);
  seg.build(1, n, 1);
}

}  // namespace HLD

namespace IN_TREE {

std::set<pii> st[N];

struct SegTree {
  int idx[N << 2];

  int lc(int u) { return u << 1; }
  int rc(int u) { return u << 1 | 1; }

  void pushup(int u) {
    if (a[idx[lc(u)]].v < a[idx[rc(u)]].v) idx[u] = idx[lc(u)];
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
  st[x].emplace(a[idx].v, idx);
  seg.modify(HLD::dfn[x], 1, n, 1, st[x].begin()->second);
}

void erase(int idx) {
  int x = a[idx].x;
  st[x].erase({a[idx].v, idx});
  if (st[x].empty()) seg.modify(HLD::dfn[x], 1, n, 1, 0);
  else seg.modify(HLD::dfn[x], 1, n, 1, st[x].begin()->second);
}

}  // namespace IN_TREE

std::stack<pii, std::vector<pii>> stk;
std::vector<int> tree[N << 2];
i64 cur, ans[N];

inline int lc(int u) { return u << 1; }
inline int rc(int u) { return u << 1 | 1; }

inline void insert(int idx) {
  cur += a[idx].v;
  IN_TREE::insert(idx);
  HLD::modify(a[idx].x, -1);
}

inline void erase(int idx) {
  cur -= a[idx].v;
  IN_TREE::erase(idx);
  HLD::modify(a[idx].x, 1);
}

bool try_insert(int idx) {
  int full = HLD::get(a[idx].x);
  if (full) {
    using HLD::in, HLD::out;
    int back = IN_TREE::seg.query(in(full), out(full), 1, n, 1);
    // std::cerr << idx << " " << back << "\n";
    if (a[back].v < a[idx].v) {
      stk.emplace(idx, back);
      insert(idx), erase(back);
      return true;
    } else {
      return false;
    }
  } else {
    stk.emplace(idx, 0);
    insert(idx);
    return true;
  }
}

inline void rollback() {
  auto [u, v] = stk.top();
  stk.pop();
  erase(u);
  if (v) insert(v);
}

void add(int l, int r, int s, int t, int u, int val) {
  if (l <= s && t <= r) return tree[u].push_back(val);
  int mid = (s + t) >> 1;
  if (mid >= l) add(l, r, s, mid, lc(u), val);
  if (mid < r) add(l, r, mid + 1, t, rc(u), val);
}

void traverse(int s, int t, int u) {
  int ins_cnt = 0;
  for (auto i : tree[u]) ins_cnt += try_insert(i);

  int mid = (s + t) >> 1;
  if (s == t) ans[s] = cur;
  else traverse(s, mid, lc(u)), traverse(mid + 1, t, rc(u));
  
  while (ins_cnt--) rollback();
}

constexpr int N = 1e5 + 50;

void solve() {
  a[0].v = 1e9;

  std::cin >> sid >> n >> k >> m;
  for (int i = 2, f; i <= n; i++) {
    std::cin >> f;
    adj[f].push_back(i);
  }
  for (int i = 1; i <= k; i++) std::cin >> a[i].x >> a[i].v;

  HLD::init();

  memset(R, -1, sizeof(R));
  for (int i = 1, opt, x, v; i <= m; i++) {
    std::cin >> opt;
    if (opt == 1) {
      std::cin >> x >> v;
      a[++k] = {x, v}, L[k] = i;
    } else {
      std::cin >> v;
      R[v] = i - 1;
    }
  }
  for (int i = 1; i <= k; i++) if (R[i] == -1) R[i] = m;
  for (int i = 1; i <= k; i++) add(L[i], R[i], 0, m, 1, i);
  traverse(0, m, 1);

  for (int i = 0; i <= m; i++) std::cout << ans[i] << " \n"[i == m];
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
