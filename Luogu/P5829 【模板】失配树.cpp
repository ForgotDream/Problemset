/**
 * @file    P5829 【模板】失配树.cpp
 * @author  ForgotDream
 * @brief   KMP + LCA
 * @date    2023-08-25
 */
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

using i64 = long long;

constexpr int N = 1e6 + 50;
std::vector<int> adj[N];
int top[N], siz[N], dep[N], fa[N], son[N];
void dfs1(int u, int frm) {
  dep[u] = dep[frm] + 1, siz[u] = 1, fa[u] = frm;
  for (auto v : adj[u]) {
    dfs1(v, u);
    siz[u] += siz[v];
    if (siz[v] > siz[son[u]]) son[u] = v;
  }
}
void dfs2(int u, int rt) {
  top[u] = rt;
  if (son[u]) dfs2(son[u], rt);
  for (auto v : adj[u]) {
    if (v == son[u]) continue;
    dfs2(v, v);
  }
}
int LCA(int u, int v) {
  while (top[u] != top[v]) {
    if (dep[top[u]] < dep[top[v]]) std::swap(u, v);
    u = fa[top[u]];
  }
  return dep[u] < dep[v] ? u : v;
}

char s[N];
int nxt[N], m, n;
void solve() {
  std::cin >> (s + 1);
  n = std::strlen(s + 1);
  for (int i = 2, j = 0; i <= n; i++) {
    while (j && s[i] != s[j + 1]) j = nxt[j];
    if (s[i] == s[j + 1]) ++j;
    nxt[i] = j;
  }
  for (int i = 1; i <= n; i++) adj[nxt[i] + 1].push_back(i + 1);
  dfs1(1, 0), dfs2(1, 1);
  std::cin >> m;
  for (int i = 1, p, q; i <= m; i++) {
    std::cin >> p >> q;
    p = fa[p + 1], q = fa[q + 1];
    // --p, --q;
    std::cout << LCA(p, q) - 1 << "\n";
  }
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}