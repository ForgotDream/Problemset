/**
 * @file    P1821 [USACO07FEB] Cow Party S.cpp
 * @author  ForgotDream
 * @brief   SSSP
 * @date    2023-11-22
 */
#include <bits/stdc++.h>

using i64 = int64_t;
using pii = std::pair<int, int>;

constexpr int N = 1050;
int n, m, s;
std::vector<pii> adj[N], rev[N];
i64 dis[2][N];
bool vis[N];
void dijkstra(int s, i64 *dis, std::vector<pii> *adj) {
  std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;
  memset(dis, 0x3f, sizeof(i64) * N);
  memset(vis, false, sizeof(bool) * N);
  dis[s] = 0, pq.emplace(0, s);
  while (!pq.empty()) {
    auto [_, u] = pq.top();
    pq.pop();
    if (vis[u]) continue;
    vis[u] = true;
    for (auto [v, w] : adj[u]) {
      if (dis[v] > dis[u] + w) dis[v] = dis[u] + w, pq.emplace(dis[v], v);
    }
  }
}
void solve() {
  std::cin >> n >> m >> s;
  for (int i = 1, u, v, w; i <= m; i++) {
    std::cin >> u >> v >> w;
    adj[u].emplace_back(v, w);
    rev[v].emplace_back(u, w);
  }
  dijkstra(s, dis[0], adj), dijkstra(s, dis[1], rev);
  i64 ans = 0;
  for (int i = 1; i <= n; i++) ans = std::max(ans, dis[0][i] + dis[1][i]);
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
