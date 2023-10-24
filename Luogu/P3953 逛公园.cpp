/**
 * @file    P3953 逛公园.cpp
 * @author  ForgotDream
 * @brief   Graph + DP
 * @date    2023-06-08
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int inf = 1e9;

void solve() {
  int n, m, k, p;
  std::cin >> n >> m >> k >> p;

  std::vector<std::vector<std::pair<int, int>>> adj(n), g(n);
  for (int i = 0; i < m; i++) {
    int u, v, w;
    std::cin >> u >> v >> w;
    u--, v--;
    adj[u].emplace_back(v, w), g[v].emplace_back(u, w);
  }

  std::vector<int> dis(n, inf);
  [&]() {
    std::vector<bool> vis(n);
    std::priority_queue<
      std::pair<int, int>,
      std::vector<std::pair<int, int>>,
      std::greater<std::pair<int, int>>
    > pq;
    pq.emplace(0, 0), dis[0] = 0;
    while (!pq.empty()) {
      int u = pq.top().second;
      pq.pop();
      if (vis[u]) { continue; }
      vis[u] = true;
      for (auto i : adj[u]) {
        int v = i.first, w = i.second;
        if (dis[v] > dis[u] + w) { dis[v] = dis[u] + w, pq.emplace(dis[v], v); }
      }
    }
  }();

  std::vector f(n, std::vector<int>(k + 1));
  std::vector ins(n, std::vector<bool>(k + 1));
  bool flg = false;
  std::function<void(int, int)> dfs = [&](int u, int cur) {
    if (cur < 0) { return 0; }
    if (ins[u][cur]) { 
      flg = true;
      return 0;
    }
    if (f[u][cur]) { return f[u][cur]; }
    int res = 0;
    ins[u][cur] = true;
    for (auto i : g[u]) {
      int v = i.first, w = i.second;
      if (dis[u] - dis[v] + cur - w < 0) { continue; }
      dfs(v, dis[u] - dis[v] + cur - w);
      (res += f[v][dis[u] - dis[v] + cur - w]) %= p;
      if (flg) { return 0; }
    }
    ins[u][cur] = false;
    return f[u][cur] = res;
  };

  dfs(0, 0), f[0][0] = 1;

  int ans = 0;
  for (int i = 0; i <= k; i++) {
    dfs(n - 1, i);
    if (flg) { 
      std::cout << -1 << "\n";
      return;
    }
    (ans += f[n - 1][i]) %= p;
  }
  std::cout << ans << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  std::cin >> t;

  while (t--) { solve(); }

  return 0;
}