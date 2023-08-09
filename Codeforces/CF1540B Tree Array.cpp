/**
 * @file    CF1540B Tree Array.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-08-07
 */
#include <bits/stdc++.h>
using i64 = long long;
constexpr int N = 250, mod = 1e9 + 7;
int n;
std::vector<int> adj[N];
i64 fastPow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}
i64 inv(i64 num) { return fastPow(num, mod - 2, mod); }
int fa[N], son[N], dep[N], siz[N], top[N];
void dfs1(int u, int frm) {
  fa[u] = frm, dep[u] = dep[frm] + 1, siz[u] = 1, son[u] = 0;
  for (auto v : adj[u]) {
    if (v == frm) continue;
    dfs1(v, u);
    siz[u] += siz[v];
    if (siz[v] > siz[son[u]]) son[u] = v;
  }
}
void dfs2(int u, int rt) {
  top[u] = rt;
  if (son[u]) dfs2(son[u], rt);
  for (auto v : adj[u]) {
    if (v == fa[u] || v == son[u]) continue;
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
i64 f[N][N], ans;
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n;
  for (int i = 1, u, v; i < n; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
  }
  int inv2 = inv(2);
  for (int i = 1; i <= n; i++) f[0][i] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      f[i][j] = (f[i - 1][j] + f[i][j - 1]) * inv2 % mod;
    }
  }
  for (int rt = 1; rt <= n; rt++) {
    dfs1(rt, 0), dfs2(rt, rt);
    for (int u = 1; u <= n; u++) {
      for (int v = 1; v < u; v++) {
        int lca = LCA(u, v);
        (ans += f[dep[u] - dep[lca]][dep[v] - dep[lca]]) %= mod;
      }
    }
  }
  std::cout << ans * inv(n) % mod << "\n";
  return 0;
}