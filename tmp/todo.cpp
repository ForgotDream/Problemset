/*
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2023-12-30
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e5 + 50;

struct LCT {
  int fa[N], ch[N][2], sum[N], val[N], rev[N];
  int &lc(int u) { return ch[u][0]; }
  int &rc(int u) { return ch[u][1]; }
  bool isRoot(int u) { return lc(fa[u]) != u && rc(fa[u]) != u; }
  int d(int u) { return rc(fa[u]) == u; }
  void pushup(int u) { sum[u] = sum[lc(u)] + sum[rc(u)] + val[u]; }
  void pushdown(int u) {
    if (!rev[u]) return;
    tagging(lc(u)), tagging(rc(u));
    rev[u] = false;
  }
  void tagging(int u) {
    if (!u) return;
    std::swap(lc(u), rc(u)), rev[u] ^= true;
  }
  void rotate(int u) {
    int f = fa[u], g = fa[f], k = d(u);
    if (!isRoot(f)) ch[g][d(f)] = u, fa[u] = g;
    ch[f][k] = ch[u][k ^ 1], ch[u][k ^ 1] && (fa[ch[u][k ^ 1]] = f);
    ch[u][k ^ 1] = f, fa[f] = u;
    pushup(f), pushup(u);
  }
  void update(int u) {
    if (fa[u]) update(fa[u]);
    pushdown(u);
  }
  void splay(int u) {
    update(u);
    for (int f = fa[u]; !isRoot(u); rotate(u), f = fa[u]) {
      if (!isRoot(f)) rotate(d(u) == d(f) ? u : f);
    }
  }
  void access(int u) {
    for (int c = 0; u; c = u, u = fa[u]) splay(u), rc(u) = c, pushup(u);
  }
  void makeRoot(int u) { access(u), splay(u), tagging(u); }
  int findRoot(int u) {
    access(u), splay(u);
    while (lc(u)) pushdown(u), u = lc(u);
    return u;
  }
  void link(int u, int v) { makeRoot(u), fa[u] = v; }
  void split(int u, int v) { makeRoot(u), access(v), splay(v); }
  void cut(int u, int v) {
    split(u, v);
    if (lc(v) != u || rc(u)) return;
    fa[u] = lc(v) = 0, pushup(v);
  }
} lct;

void solve() {
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
