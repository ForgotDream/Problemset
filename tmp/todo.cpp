/**
 * @file
 * @author  ForgotDream
 * @brief
 * @date    2023-10-17
 */
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>

using i64 = long long;
using pii = std::pair<int, int>;
using pli = std::pair<i64, int>;

constexpr int N = 1e5 + 50, M = 20;
int n, m, c;
std::vector<pii> adj[N];
i64 a[N], b[M];
bool vis[N];
i64 dis[M][N], f[M][1 << M];
void dijkstra(int s, i64 *dis) {
  memset(vis, false, sizeof(vis)), memset(dis, 0x3f, sizeof(int) * N);
  std::priority_queue<pli, std::vector<pli>, std::greater<>> pq;
  dis[s] = 0, pq.emplace(0, s);
  while (!pq.empty()) {
    int u = pq.top().second;
    pq.pop();
    if (vis[u]) continue;
    vis[u] = true;
    for (auto [v, w] : adj[u]) {
      if (dis[v] > dis[u] + w) {
        dis[v] = dis[u] + w;
        if (v >= c) pq.emplace(dis[v], v);
      }
    }
  }
}
void solve() {
  std::cin >> n >> m >> c;
  for (int i = 0; i < n; i++) std::cin >> a[i];
  for (int i = 0; i < c; i++) std::cin >> b[i];
  for (int i = 1, u, v, w; i <= m; i++) {
    std::cin >> u >> v >> w;
    adj[u].emplace_back(v, w), adj[v].emplace_back(u, w);
  }
  memset(f, 0x3f, sizeof(f));
  for (int i = 0; i < c; i++) dijkstra(i, dis[i]), f[i][1 << i] = 0;
  int mask = (1 << c) - 1;
  for (int i = 0; i <= mask; i++) {
    for (int j = 0; j < c; j++) {
      if (!(i & (1 << j))) continue;
      for (int k = 0; k < c; k++) {
        if (i & (1 << k)) continue;
        int p = i | (1 << k);
        f[k][p] = std::min(f[k][p], f[j][i] + dis[j][k]);
      }
    }
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
