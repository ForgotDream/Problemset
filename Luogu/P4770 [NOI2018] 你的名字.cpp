/*
 * @file    P4770 [NOI2018] 你的名字.cpp
 * @author  ForgotDream
 * @brief   SAM + Segment Tree
 * @date    2024-01-23
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 1e6 + 50;

std::string s, t;
int n, m, q;

struct SAM {
  int ch[N][26], len[N], link[N], cnt = 1, lst = 1;
  void clear() {
    for (int i = 1; i <= cnt; i++) {
      len[i] = link[i] = 0;
      memset(ch[i], 0, sizeof(ch[i]));
    }
    cnt = lst = 1;
  }
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
} ssam, tsam;

struct SegTree {
  struct Node {
    int lc, rc, mx;
  } tree[N << 5];
  int cnt;
  
  int &lc(int u) { return tree[u].lc; }
  int &rc(int u) { return tree[u].rc; }

  void pushup(int u) {
    tree[u].mx = std::max(tree[lc(u)].mx, tree[rc(u)].mx);
  }

  void modify(int tar, int s, int t, int &u) {
    if (!u) u = ++cnt;
    if (s == t) return tree[u].mx = tar, void();
    int mid = (s + t) >> 1;
    if (mid >= tar) modify(tar, s, mid, lc(u));
    else modify(tar, mid + 1, t, rc(u));
    pushup(u);
  }
  int merge(int s, int t, int u, int v) {
    if (!u || !v) return u + v;
    int p = ++cnt;
    if (s == t) return tree[p].mx = std::max(tree[u].mx, tree[v].mx), p;
    int mid = (s + t) >> 1;
    lc(p) = merge(s, mid, lc(u), lc(v));
    rc(p) = merge(mid + 1, t, rc(u), rc(v));
    pushup(p);
    return p;
  }
  int query(int l, int r, int s, int t, int u) {
    if (!u) return 0;
    if (l <= s && t <= r) return tree[u].mx;
    int mid = (s + t) >> 1, res = 0;
    if (mid >= l) res = std::max(res, query(l, r, s, mid, lc(u)));
    if (mid < r) res = std::max(res, query(l, r, mid + 1, t, rc(u)));
    return res;
  }
} seg;
int rt[N];

int pos[N], f[N], g[N];

std::vector<int> adj[N];

void dfs(int u) {
  for (auto v : adj[u]) dfs(v), rt[u] = seg.merge(1, n, rt[u], rt[v]);
}

i64 calc_all(int u) {
  i64 res = 0;
  for (auto v : adj[u]) res += tsam.len[v] - tsam.len[u] + calc_all(v);
  return res;
}
i64 calc_unique(int u) {
  i64 res = 0;
  for (auto v : adj[u]) res += g[v] - tsam.len[u] + calc_unique(v);
  // for (auto v : adj[u]) res += f[v] - tsam.len[u] + calc_unique(v);
  return res;
}

void tagging(int u) {
  for (auto v : adj[u]) tagging(v), f[u] = std::max(f[u], f[v]);
  g[u] = std::max(g[u], std::min(tsam.len[u], f[u]));
}

void solve() {
  std::cin >> s >> q, n = s.length();
  for (int i = 0; i < n; i++) pos[i + 1] = ssam.expand(s[i] - 'a');

  m = ssam.cnt;
  for (int i = 2; i <= m; i++) adj[ssam.link[i]].push_back(i);
  for (int i = 1; i <= n; i++) seg.modify(i, 0, n, rt[pos[i]]);
  dfs(1);
  // std::cerr << "?" << seg.query(1, n, 1, n, rt[1]) << "\n";
  for (int i = 1; i <= m; i++) adj[i].clear();

  for (int l, r; q; q--) {
    std::cin >> t >> l >> r, tsam.clear();
    for (auto c : t) tsam.expand(c - 'a');
    for (int i = 1; i <= tsam.cnt; i++) {
      adj[i].clear(), f[i] = 0;
      g[i] = tsam.len[tsam.link[i]];
    }
    for (int i = 2; i <= tsam.cnt; i++) adj[tsam.link[i]].push_back(i);

    auto query = [&](int u) { return seg.query(0, r, 0, n, rt[u]); };

    int ps = 1, pt = 1, cur = 0;
    for (auto c : t) {
      int d = c - 'a';
      pt = tsam.ch[pt][d];

      bool flg = false;
      while (ps != 1) {
        if (ssam.ch[ps][d]) {
          int tmp = query(ssam.ch[ps][d]) - l + 1;
          if (ssam.len[ssam.link[ps]] < tmp) {
            flg = true, cur = std::min(cur + 1, tmp);
            ps = ssam.ch[ps][d];
            break;
          }
        }
        ps = ssam.link[ps], cur = ssam.len[ps];
      }
      if (!flg) {
        if (!ssam.ch[ps][d] || query(ssam.ch[ps][d]) < l) cur = 0;
        else ps = ssam.ch[ps][d], cur++;
      }

      f[pt] = std::max(f[pt], cur);

      // int k = pt;
      // for (; k != 1 && tsam.len[tsam.link[k]] >= cur; k = tsam.link[k]);
      // for (; k != 1 && tsam.len[k] > f[k]; k = tsam.link[k]) {
      //   f[k] = std::max(f[k], std::min(tsam.len[k], cur));
      // }
    }

    tagging(1);
    std::cout << calc_all(1) - calc_unique(1) << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
