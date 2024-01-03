/*
 * @file    P3565 [POI2014] HOT-Hotels.cpp
 * @author  ForgotDream
 * @brief   长链剖分 + DP
 * @date    2024-01-03
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 50;
int n;
std::vector<int> adj[N];

int dep[N], len[N], fa[N], son[N];
void dfs1(int u, int frm) {
  dep[u] = dep[frm] + 1, len[u] = 1, fa[u] = frm;
  for (auto v : adj[u]) {
    if (v == frm) continue;
    dfs1(v, u);
    if (len[v] + 1 > len[u]) len[u] = len[v] + 1, son[u] = v;
  }
}

i64 buf[N << 2], *f[N], *g[N], *p = buf, ans;
void dp(int u) {
  if (son[u]) f[son[u]] = f[u] + 1, g[son[u]] = g[u] - 1, dp(son[u]);
  f[u][0] = 1, ans += g[u][0];
  for (auto v : adj[u]) {
    if (v == fa[u] || v == son[u]) continue;
    f[v] = p, p += len[v] << 1, g[v] = p, p += len[v] << 1;
    dp(v);
    for (int i = 0; i < len[v]; i++) {
      if (i) ans += g[v][i] * f[u][i - 1];
      ans += g[u][i + 1] * f[v][i];
    }
    for (int i = 0; i < len[v]; i++) {
      g[u][i + 1] += f[u][i + 1] * f[v][i];
      if (i) g[u][i - 1] += g[v][i];
      f[u][i + 1] += f[v][i];
    }
  }
}

void solve() {
  std::cin >> n;
  for (int i = 1, u, v; i < n; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
  }

  dfs1(1, 0);
  f[1] = p, p += len[1] << 1, g[1] = p, p += len[1] << 1;
  dp(1);
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
