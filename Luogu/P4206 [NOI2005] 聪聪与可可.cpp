/**
 * @file    P4206 [NOI2005] 聪聪与可可.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-11-22
 */
#include <bits/stdc++.h>

using i64 = int64_t;
using f64 = double;

constexpr int N = 1050;
int n, m, a, b;
std::vector<int> adj[N];
f64 f[N][N];
int dis[N][N];
bool vis[N];
void bfs(int s) {
  std::queue<int> q;
  memset(vis, false, sizeof(vis));
  q.push(s), vis[s] = true;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (auto v : adj[u]) {
      if (vis[v]) continue;
      dis[s][v] = dis[s][u] + 1, vis[v] = true;
      q.push(v);
    }
  }
}
bool used[N][N];
f64 dfs(int i, int j) {
  if (used[i][j]) return f[i][j];
  used[i][j] = true;
  if (i == j) return f[i][j] = 0;
  if (dis[i][j] <= 2) return f[i][j] = 1;
  int p = *std::min_element(adj[i].begin(), adj[i].end(), [&](auto lhs, auto rhs) {
    return std::tie(dis[j][lhs], lhs) < std::tie(dis[j][rhs], rhs);
  });
  int q = *std::min_element(adj[p].begin(), adj[p].end(), [&](auto lhs, auto rhs) {
    return std::tie(dis[j][lhs], lhs) < std::tie(dis[j][rhs], rhs);
  });
  for (auto v : adj[j]) f[i][j] += dfs(q, v);
  f[i][j] += dfs(q, j);
  f[i][j] = f[i][j] / (1 + adj[j].size()) + 1;
  return f[i][j];
}
void solve() {
  std::cin >> n >> m >> a >> b;
  for (int i = 1, u, v; i <= m; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
  }
  for (int i = 1; i <= n; i++) bfs(i);
  std::cout << std::fixed << std::setprecision(3) << dfs(a, b) << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
