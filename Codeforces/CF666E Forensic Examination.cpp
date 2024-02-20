/*
 * @file    CF666E Forensic Examination.cpp
 * @author  ForgotDream
 * @brief   GSAM + Segment Tree
 * @date    2024-02-20
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;
using pii = std::pair<int, int>;

constexpr int N = 1e6 + 50;

struct GSAM {
  int ch[N][26], len[N], link[N], cnt = 1;

  int expand(int p, int d) {
    if (int q = ch[p][d]) {
      if (len[p] + 1 == len[q]) {
        return q;
      } else {
        int t = ++cnt;
        len[t] = len[p] + 1, link[t] = link[q];
        memcpy(ch[t], ch[q], sizeof(ch[t]));
        for (; p && ch[p][d] == q; p = link[p]) ch[p][d] = t;
        link[q] = t;
        return t;
      }
    }
    int c = ++cnt;
    len[c] = len[p] + 1;
    for (; p && !ch[p][d]; p = link[p]) ch[p][d] = c;
    if (!p) {
      link[c] = 1;
    } else {
      int q = ch[p][d];
      if (len[p] + 1 == len[q]) {
        link[c] = q;
      } else {
        int t = ++cnt;
        len[t] = len[p] + 1, link[t] = link[q];
        memcpy(ch[t], ch[q], sizeof(ch[t]));
        for (; p && ch[p][d] == q; p = link[p]) ch[p][d] = t;
        link[c] = link[q] = t;
      }
    }
    return c;
  }
} gsam;

struct SegTree {
  struct Node {
    int lc, rc, mx, idx;
  } tree[N << 5];
  int cnt;

  int &lc(int u) { return tree[u].lc; }
  int &rc(int u) { return tree[u].rc; }

  void pushup(int u) {
    if (tree[lc(u)].mx >= tree[rc(u)].mx) {
      tree[u].mx = tree[lc(u)].mx, tree[u].idx = tree[lc(u)].idx;
    } else {
      tree[u].mx = tree[rc(u)].mx, tree[u].idx = tree[rc(u)].idx;
    }
  }

  void modify(int tar, int s, int t, int &u) {
    if (!u) u = ++cnt;
    if (s == t) return tree[u].mx++, tree[u].idx = tar, void();
    int mid = (s + t) >> 1;
    if (mid >= tar) modify(tar, s, mid, lc(u));
    else modify(tar, mid + 1, t, rc(u));
    pushup(u);
  }
  
  int merge(int s, int t, int u, int v) {
    if (!u || !v) return u + v;
    int p = ++cnt;
    if (s == t) {
      tree[p] = tree[u], tree[p].mx += tree[v].mx;
      return p;
    }
    int mid = (s + t) >> 1;
    lc(p) = merge(s, mid, lc(u), lc(v));
    rc(p) = merge(mid + 1, t, rc(u), rc(v));
    pushup(p);
    return p;
  }

  pii query(int l, int r, int s, int t, int u) {
    if (!u) return {0, -1e9};
    if (l <= s && t <= r) return {tree[u].mx, -tree[u].idx};
    int mid = (s + t) >> 1;
    pii res = {0, -1e9};
    if (mid >= l) res = std::max(res, query(l, r, s, mid, lc(u)));
    if (mid < r) res = std::max(res, query(l, r, mid + 1, t, rc(u)));
    return res;
  }
} seg;
int rt[N];

char s[N];
int n, q, m;

std::vector<int> adj[N];
int fa[20][N];

void dfs(int u) {
  for (int i = 1; i <= std::__lg(m); i++) fa[i][u] = fa[i - 1][fa[i - 1][u]];
  for (auto v : adj[u]) {
    fa[0][v] = u, dfs(v);
    rt[u] = seg.merge(1, n, rt[u], rt[v]);
  }
}

int pos[N], max_len[N];

inline int find(int l, int r) {
  int u = pos[r], len = r - l + 1;
  for (int i = std::__lg(m); ~i; i--) {
    if (gsam.len[fa[i][u]] >= len) u = fa[i][u]; 
  }
  return u;
}

void solve() {
  std::cin >> (s + 1) >> n;
  for (int i = 1, lst = 1; i <= n; i++, lst = 1) {
    std::string t;
    std::cin >> t;
    for (auto c : t) {
      lst = gsam.expand(lst, c - 'a');
      seg.modify(i, 1, n, rt[lst]);
    }
  }
  m = gsam.cnt;

  for (int i = 2; i <= m; i++) adj[gsam.link[i]].push_back(i);
  dfs(1);

  for (int i = 1, p = 1, l = 0; s[i]; i++) {
    int d = s[i] - 'a';
    while (p && !gsam.ch[p][d]) p = gsam.link[p], l = gsam.len[p];
    if (!p) p = 1, l = 0;
    else p = gsam.ch[p][d], l++;
    pos[i] = p, max_len[i] = l;
  }

  std::cin >> q;
  for (int l, r, pl, pr; q; q--) {
    std::cin >> l >> r >> pl >> pr;
    int len = pr - pl + 1;

    if (max_len[pr] < len) {
      std::cout << l << " " << 0 << "\n";
      continue;
    }

    auto [mx, idx] = seg.query(l, r, 1, n, rt[find(pl, pr)]);
    idx = -idx;

    if (mx == 0) idx = l;
    std::cout << idx << " " << mx << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
