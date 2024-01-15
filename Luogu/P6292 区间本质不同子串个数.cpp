/*
 * @file    P6292 区间本质不同子串个数.cpp
 * @author  ForgotDream
 * @brief   LCT + SAM + Segment Tree
 * @date    2024-01-14
 */
#include <bits/stdc++.h>

using i64 = long long;
using pii = std::pair<int, int>;

constexpr int N = 2e5 + 50;

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

int pos[N];

struct BIT {
  i64 s[N], d[N];
  // 加公差为 1，首项为 val 的等差数列
  void modify(int u, i64 val) {
    for (int i = u; i < N; i += i & -i) s[i] += u * val, d[i] += val;
  }
  i64 query(int u) {
    i64 t1 = 0, t2 = 0;
    for (int i = u; i; i -= i & -i) t1 += s[i], t2 += d[i];
    return t2 * (u + 1) - t1;
  }
  void modify(int l, int r, int v) { modify(l, v), modify(r + 1, -v); }
  i64 query(int l, int r) { return query(r) - query(l - 1); }
} bit;

struct LCT {
  int ch[N][2], fa[N], val[N], len[N], lst[N], tag[N];
  inline int d(int u) { return ch[fa[u]][1] == u; }
  inline bool isRoot(int u) { return ch[fa[u]][0] != u && ch[fa[u]][1] != u; }
  inline void pushup(int u) {
    val[u] = std::min({val[ch[u][0]], val[ch[u][1]], len[u]});
  }
  inline void pushdown(int u) {
    if (!tag[u]) return;
    tagging(ch[u][0], tag[u]), tagging(ch[u][1], tag[u]);
    tag[u] = 0;
  }
  inline void tagging(int u, int val) { lst[u] = tag[u] = val; }
  inline void update(int u) { (fa[u] ? update(fa[u]) : void()), pushdown(u); }
  void rotate(int u) {
    int f = fa[u], g = fa[f], k = d(u);
    if (!isRoot(f)) ch[g][d(f)] = u;
    ch[f][k] = ch[u][!k], ch[u][!k] && (fa[ch[u][!k]] = f);
    ch[u][!k] = f, fa[f] = u, fa[u] = g;
    pushup(f), pushup(u);
  }
  void splay(int u) {
    update(u);
    for (int f = fa[u]; !isRoot(u); rotate(u), f = fa[u]) {
      if (!isRoot(f)) rotate(d(u) == d(f) ? f : u);
    }
  }
  void access(int u) {
    for (int c = 0; u; c = u, u = fa[u]) {
      splay(u), ch[u][1] = c, pushup(u);
      if (lst[u]) bit.modify(lst[u] - sam.len[u] + 1, lst[u] - val[u] + 1, -1);
    }
  }
  void init() {
    val[0] = 2e9;
    for (int i = 1; i <= sam.cnt; i++) {
      fa[i] = sam.link[i];
      val[i] = len[i] = sam.len[fa[i]] + 1;
      tag[i] = ch[i][0] = ch[i][1] = 0;
    }
  }
} lct;

i64 ans[N];

void solve() {
  std::cin >> (s + 1) >> m, n = strlen(s + 1);
  for (int l, r, i = 1; i <= m; i++) {
    std::cin >> l >> r;
    qry[r].emplace_back(l, i);
  }

  for (int i = 1; i <= n; i++) sam.expand(s[i]), pos[i] = sam.lst;
  lct.init();

  for (int r = 1; r <= n; r++) {
    lct.access(pos[r]);
    lct.splay(pos[r]), lct.tagging(pos[r], r);
    bit.modify(r - sam.len[pos[r]] + 1, r, 1);
    for (auto [l, i] : qry[r]) ans[i] = bit.query(l, r);
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
