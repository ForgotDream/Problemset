/*
 * @file    P5903 【模板】树上 K 级祖先.cpp
 * @author  ForgotDream
 * @brief   长链剖分
 * @date    2024-01-01
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 5e5 + 50;
int n, q, rt, fa[20][N];
u32 s;
std::vector<int> adj[N];

inline u32 get(u32 u) {
  u ^= u << 13;
  u ^= u >> 17;
  u ^= u << 5;
  return s = u;
}

int dep[N], son[N], len[N];
void dfs1(int u) {
  len[u] = 1, dep[u] = dep[fa[0][u]] + 1;
  for (int i = 1; i <= std::__lg(n); i++) fa[i][u] = fa[i - 1][fa[i - 1][u]];
  for (auto v : adj[u]) {
    dfs1(v);
    if (len[v] + 1 > len[u]) len[u] = len[v] + 1, son[u] = v;
  }
}
int top[N], dfn[N], idfn[N], clk;
std::vector<int> up[N], dn[N];
void dfs2(int u, int tp) {
  top[u] = tp, dfn[u] = ++clk, idfn[clk] = u;
  if (son[u]) dfs2(son[u], tp);
  for (auto v : adj[u]) if (v != son[u]) dfs2(v, v);
}

void init() {
  dfs1(rt), dfs2(rt, rt);
  for (int i = 1; i <= n; i++) {
    if (i != top[i]) continue;
    for (int j = 0, p = i; j < len[i]; j++, p = fa[0][p]) up[i].push_back(p);
    for (int j = 0; j < len[i]; j++) dn[i].push_back(idfn[dfn[i] + j]);
  }
}
inline int query(int u, int k) {
  if (k == 0) return u;
  int p = std::__lg(k), f = fa[p][u], tp = top[f];
  int d = k - (1 << p) + dep[tp] - dep[f];
  if (d > 0) return up[tp][d];
  else return dn[tp][-d];
}

void solve() {
  std::cin >> n >> q >> s;
  for (int i = 1; i <= n; i++) {
    std::cin >> fa[0][i];
    if (fa[0][i]) adj[fa[0][i]].push_back(i);
    else rt = i;
  }

  init();

  int lst = 0;
  i64 ans = 0;
  for (int i = 1, u, k; i <= q; i++) {
    u = (get(s) ^ lst) % n + 1, k = (get(s) ^ lst) % dep[u];
    lst = query(u, k), ans ^= 1ll * i * lst;
    // std::cerr << u << " " << k << " " << lst << "\n";
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
