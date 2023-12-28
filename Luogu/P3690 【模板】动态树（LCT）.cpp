/*
 * @file    P3690 【模板】动态树（LCT）.cpp
 * @author  ForgotDream
 * @brief   LCT
 * @date    2023-12-28
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 50;
int n, m;

struct LCT {
  int ch[N][2], siz[N], tag[N], fa[N], val[N], sum[N];
  int d(int u) { return ch[fa[u]][1] == u; }
  bool isRoot(int u) { return ch[fa[u]][0] != u && ch[fa[u]][1] != u; }
  void pushup(int u) { 
    siz[u] = siz[ch[u][0]] + siz[ch[u][1]] + 1; 
    sum[u] = sum[ch[u][0]] ^ sum[ch[u][1]] ^ val[u];
  }
  void pushdown(int u) {
    if (!tag[u]) return;
    tagging(ch[u][0]), tagging(ch[u][1]);
    tag[u] = false;
  }
  void tagging(int u) {
    if (!u) return;
    std::swap(ch[u][0], ch[u][1]), tag[u] ^= true;
  }
  void rotate(int u) {
    int f = fa[u], g = fa[f], k = d(u);
    if (!isRoot(f)) ch[g][d(f)] = u;
    ch[f][k] = ch[u][!k], fa[ch[u][!k]] && (fa[ch[u][!k]] = f);
    ch[u][!k] = f, fa[f] = u, fa[u] = g;
    pushup(f), pushup(u);
  }
  void update(int u) {
    if (!isRoot(u)) update(fa[u]);
    pushdown(u);
  }
  void splay(int u) {
    update(u);
    for (int f = fa[u]; !isRoot(u); rotate(u), f = fa[u]) {
      if (!isRoot(f)) rotate(d(f) == d(u) ? f : u);
    }
  }
  void access(int u) {
    for (int c = 0; u; c = u, u = fa[u]) splay(u), ch[u][1] = c, pushup(u);
  }
  void makeRoot(int u) { access(u), splay(u), tagging(u); }
  int findRoot(int u) {
    access(u), splay(u);
    while (ch[u][0]) pushdown(u), u = ch[u][0];
    return u;
  }
  void link(int u, int v) { makeRoot(u), fa[u] = v; }
  void split(int u, int v) { makeRoot(u), access(v), splay(v); }
  void cut(int u, int v) {
    split(u, v);
    if (ch[v][0] != u || ch[u][1]) return;
    fa[u] = ch[v][0] = 0;
    pushup(v);
  }
} lct;

void solve() {
  std::cin >> n >> m;
  for (int i = 1, v; i <= n; i++) {
    std::cin >> v, lct.siz[i] = 1, lct.val[i] = lct.sum[i] = v;
  }

  for (int i = 1, opt, u, v; i <= m; i++) {
    std::cin >> opt >> u >> v;
    if (opt == 0) {
      lct.split(u, v), std::cout << lct.sum[v] << "\n";
    } else if (opt == 1) {
      if (lct.findRoot(u) == lct.findRoot(v)) continue;
      lct.link(u, v);
    } else if (opt == 2) {
      lct.cut(u, v);
    } else {
      lct.splay(u), lct.val[u] = v;
    }
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
