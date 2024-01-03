/*
 * @file    P4362 [NOI2002] 贪吃的九头龙.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2024-01-01
 */
#include <bits/stdc++.h>

using i64 = long long;
using pii = std::pair<int, int>;

// 限制是 1 所在的联通块大小恰好为 k
// 感觉有点难刻画

constexpr int N = 305;
int n, m, k;
std::vector<pii> adj[N];

int f[N][N][2], g[N][2];
// f[i][j][k]
// i -> 当前节点
// j -> 1 所在联通块大小
// k -> 是否与 1 连通

void dfs(int u, int frm) {
  f[u][0][0] = f[u][1][1] = 0;
  for (auto [v, w] : adj[u]) {
    if (v == frm) continue;
    dfs(v, u);
    memcpy(g, f[u], sizeof(f[u]));
    memset(f[u], 0x3f, sizeof(f[u]));
    for (int i = 0; i <= k; i++) {
      for (int j = 0; j <= i; j++) {
        f[u][i][0] = std::min(f[u][i][0], f[v][j][0] + g[i - j][0] + (m == 2) * w);
        f[u][i][0] = std::min(f[u][i][0], f[v][j][1] + g[i - j][0]);
        f[u][i][1] = std::min(f[u][i][1], f[v][j][1] + g[i - j][1] + w);
        f[u][i][1] = std::min(f[u][i][1], f[v][j][0] + g[i - j][1]);
      }
    }
  }
}

void solve() {
  std::cin >> n >> m >> k;
  if (m > n - k - 1) return std::cout << -1 << "\n", void();

  for (int i = 1, u, v, w; i < n; i++) {
    std::cin >> u >> v >> w;
    adj[u].emplace_back(v, w), adj[v].emplace_back(u, w);
  }

  memset(f, 0x3f, sizeof(f));
  dfs(1, 0);
  std::cout << f[1][k][1] << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
