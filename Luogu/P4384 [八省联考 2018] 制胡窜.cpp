/*
 * @file    P4384 [八省联考 2018] 制胡窜.cpp
 * @author  ForgotDream
 * @brief   String + SAM + Segment Tree
 * @date    2024-02-19
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 2e5 + 50, inf = 0x3f3f3f3f;

struct SAM {
  int ch[N][10], len[N], link[N], cnt = 1, lst = 1;

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
        link[q] = link[cur] = tmp;
      }
    }
    return lst = cur;
  }
} sam;

struct SegTree {
  struct Node {
    int mx = 0, mn = 0;
    i64 s1 = 0, s2 = 0;

    friend Node operator+(const Node &lhs, const Node &rhs) {
      if (lhs.mn == 0) return rhs;
      if (rhs.mn == 0) return lhs;
      Node res;
      res.mx = std::max(lhs.mx, rhs.mx), res.mn = std::min(lhs.mn, rhs.mn);
      res.s1 = lhs.s1 + rhs.s1 + rhs.mn * (rhs.mn - lhs.mx);
      res.s2 = lhs.s2 + rhs.s2 + rhs.mn - lhs.mx;
      return res;
    }
  } tree[N << 5];
  int cnt, lc[N << 5], rc[N << 5];

  void pushup(int u) { tree[u] = tree[lc[u]] + tree[rc[u]]; }

  void modify(int tar, int s, int t, int &u, int val) {
    if (!u) u = ++cnt;
    if (s == t) {
      tree[u].mx = tree[u].mn = val;
      tree[u].s1 = tree[u].s2 = 0;
      return;
    }
    int mid = (s + t) >> 1;
    if (mid >= tar) modify(tar, s, mid, lc[u], val);
    else modify(tar, mid + 1, t, rc[u], val);
    pushup(u);
  }

  int merge(int s, int t, int u, int v) {
    if (!u || !v) return u + v;
    // if (s == t) return tree[++cnt] = tree[u] + tree[v], cnt; // 这种情况实际上是不存在的
    int mid = (s + t) >> 1, p = ++cnt;
    lc[p] = merge(s, mid, lc[u], lc[v]);
    rc[p] = merge(mid + 1, t, rc[u], rc[v]);
    pushup(p);
    return p;
  }

  int query_max(int l, int r, int s, int t, int u) {
    if (!u) return 0;
    if (l <= s && t <= r) return tree[u].mx;
    int mid = (s + t) >> 1, res = 0;
    if (mid >= l) res = std::max(res, query_max(l, r, s, mid, lc[u]));
    if (mid < r) res = std::max(res, query_max(l, r, mid + 1, t, rc[u]));
    return res;
  }

  int query_min(int l, int r, int s, int t, int u) {
    if (!u) return inf;
    if (l <= s && t <= r) return tree[u].mn;
    int mid = (s + t) >> 1, res = inf;
    if (mid >= l) res = std::min(res, query_min(l, r, s, mid, lc[u]));
    if (mid < r) res = std::min(res, query_min(l, r, mid + 1, t, rc[u]));
    return res;
  }

  Node query(int l, int r, int s, int t, int u) {
    if (!u) return tree[0];
    if (l <= s && t <= r) return tree[u];
    int mid = (s + t) >> 1;
    Node res;
    if (mid >= l) res = res + query(l, r, s, mid, lc[u]);
    if (mid < r) res = res + query(l, r, mid + 1, t, rc[u]);
    return res;
  }
} seg;
int rt[N];

int n, q, m;
char s[N];

int pos[N];
std::vector<int> adj[N];

int fa[20][N];

void dfs(int u, int frm) {
  fa[0][u] = frm;
  for (int i = 1; i <= std::__lg(m); i++) fa[i][u] = fa[i - 1][fa[i - 1][u]];
  for (auto v : adj[u]) {
    dfs(v, u);
    rt[u] = seg.merge(1, n, rt[u], rt[v]);
  }
}

inline int find(int l, int r) {
  int len = r - l + 1, u = pos[r];
  for (int i = std::__lg(m); ~i; i--) {
    if (sam.len[fa[i][u]] >= len) u = fa[i][u];
  }
  return u;
}

inline i64 full(i64 len) {
  if (len < 2) return 0;
  return len * (len - 1) / 2;
}

i64 query(int l, int r) {
  int u = find(l, r), len = r - l + 1;
  int lp = seg.tree[rt[u]].mn, rp = seg.tree[rt[u]].mx;
  // std::cerr << u << " " << lp << " " << rp << "\n";

  if (lp < rp - 2 * len + 1 && 
      seg.query_max(lp, rp - len, 1, n, rt[u]) - len + 1 > lp) {  // 不相交
    return full(n - 1);
  }

  if (rp - len + 1 <= lp) {
    auto cur = seg.tree[rt[u]];
    int t = rp - len + 1;
    i64 res = cur.s1 - cur.s2 * t + full(lp - t) + 1ll * (lp - t) * (n - len);
    return full(n - 1) - res;
  }

  int t = rp - len + 1, q = seg.query_max(1, t, 1, n, rt[u]);
  auto cur = seg.query(q, lp + len - 1, 1, n, rt[u]);

  int p1 = seg.query_max(1, lp + len - 1, 1, n, rt[u]);
  int p2 = seg.query_min(lp + len, n, 1, n, rt[u]);

  i64 res = cur.s1 - cur.s2 * t;
  if (p2 > t) res += 1ll * (lp - (p1 - len + 1)) * (p2 - t);
  return full(n - 1) - res;
}

void solve() {
  std::cin >> n >> q >> (s + 1);
  for (int i = 1; i <= n; i++) pos[i] = sam.expand(s[i] - '0');
  m = sam.cnt;

  for (int i = 2; i <= m; i++) adj[sam.link[i]].push_back(i);
  for (int i = 1; i <= n; i++) seg.modify(i, 1, n, rt[pos[i]], i);
  dfs(1, 0);

  for (int i = 1, l, r; i <= q; i++) {
    std::cin >> l >> r;
    std::cout << query(l, r) << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
