/**
 * @file
 * @author  ForgotDream
 * @brief
 * @date    2023-10-13
 */
#include <iostream>
#include <cstring>
#include <queue>
#include <vector>

using i64 = long long;
using pii = std::pair<int, int>;
using pli = std::pair<i64, int>;

constexpr int N = 2e4 + 50, K = 205;
int n, m, k, q;
std::vector<pii> adj[N];
i64 dis[K][N];
bool vis[N];
void dijkstra(int s, i64 *dis) {
  std::memset(dis, 0x3f, sizeof(i64) * N);
  std::memset(vis, false, sizeof(vis));
  std::priority_queue<pli, std::vector<pli>, std::greater<>> pq;
  dis[s] = 0, pq.emplace(0, s);
  while (!pq.empty()) {
    int u = pq.top().second;
    pq.pop();
    if (vis[u]) continue;
    vis[u] = true;
    for (auto [v, w] : adj[u]) {
      if (dis[v] > dis[u] + w) dis[v] = dis[u] + w, pq.emplace(dis[v], v);
    }
  }
}
void solve() {
  std::cin >> n >> m >> k >> q;
  for (int i = 1, u, v, w; i <= m; i++) {
    std::cin >> u >> v >> w;
    adj[u].emplace_back(v, w);
  }
  for (int i = 1, u; i <= k; i++) std::cin >> u, dijkstra(u, dis[i]);
  for (int i = 1, u, v; i <= q; i++) {
    std::cin >> u >> v;
    i64 ans = 1e18;
    for (int j = 1; j <= k; j++) ans = std::min(ans, dis[j][u] + dis[j][v]);
    std::cout << ans << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
