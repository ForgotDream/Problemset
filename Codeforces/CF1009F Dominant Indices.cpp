/*
 * @file    CF1009F Dominant Indices.cpp
 * @author  ForgotDream
 * @brief   长链剖分
 * @date    2024-01-01
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e6 + 50, M = 1;
int n;
std::vector<int> adj[N / M];

int dep[N], len[N], son[N], fa[N];
void dfs1(int u, int frm) {
  len[u] = 1, dep[u] = dep[frm] + 1, fa[u] = frm;
  for (auto v : adj[u]) {
    if (v == frm) continue;
    dfs1(v, u);
    if (len[v] + 1 > len[u]) len[u] = len[v] + 1, son[u] = v;
  }
}
int top[N], dfn[N], idfn[N], clk;
int buf[N], *f[N];
void dfs2(int u, int tp) {
  top[u] = tp, dfn[u] = ++clk, idfn[clk] = u;
  f[u] = buf + clk;
  if (son[u]) dfs2(son[u], tp);
  for (auto v : adj[u]) {
    if (v == son[u] || v == fa[u]) continue;
    dfs2(v, v);
  }
}

int ans[N];
void dp(int u) {
  if (son[u]) dp(son[u]), ans[u] = ans[son[u]] + 1;
  f[u][0] = 1;
  if (f[u][ans[u]] <= 1) ans[u] = 0;
  for (auto v : adj[u]) {
    if (v == son[u] || v == fa[u]) continue;
    dp(v);
    for (int i = 1; i <= len[v]; i++) {
      f[u][i] += f[v][i - 1];
      if (f[u][i] > f[u][ans[u]] ||
          (f[u][i] == f[u][ans[u]] && i < ans[u])) {
        ans[u] = i;
      }
    }
  }
}

void solve() {
  std::cin >> n;
  for (int i = 1, u, v; i < n; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
  }

  dfs1(1, 0), dfs2(1, 1);
  dp(1);

  for (int i = 1; i <= n; i++) std::cout << ans[i] << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
