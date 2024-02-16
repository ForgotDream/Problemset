/*
 * @file    CF1495D BFS Trees.cpp
 * @author  ForgotDream
 * @brief   BFS
 * @date    2024-02-14
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 450, mod = 998244353;

int n, m;
std::vector<int> adj[N];

int cnt[N][N], dis[N][N];

void bfs(int s) {
  std::queue<int> q;
  memset(dis[s], 0x3f, sizeof(dis[s]));
  q.push(s), cnt[s][s] = 1, dis[s][s] = 0;

  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (auto v : adj[u]) {
      if (dis[s][v] > dis[s][u] + 1) {
        dis[s][v] = dis[s][u] + 1;
        cnt[s][v] = cnt[s][u];
        q.push(v);
      } else if (dis[s][v] == dis[s][u] + 1) {
        cnt[s][v] = std::min(cnt[s][v] + cnt[s][u], 2);
      }
    }
  }
}

int calc(int u, int v) {
  int res = 1;
  for (int i = 1; i <= n; i++) {
    if (dis[u][i] + dis[v][i] == dis[u][v]) continue;  // 意味着这个点在 u，v 的最短路上
    int cur = 0;
    for (auto j : adj[i]) {
      if (dis[u][i] == dis[u][j] + 1 && dis[v][i] == dis[v][j] + 1) cur++;
    }
    res = 1ll * res * cur % mod;
  }
  return res;
}

void solve() {
  std::cin >> n >> m;
  for (int i = 1, u, v; i <= m; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
  }
  for (int i = 1; i <= n; i++) bfs(i);

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (cnt[i][j] == 2) {
        std::cout << 0 << " ";
        continue;
      }
      std::cout << calc(i, j) << " ";
    }
    std::cout << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
