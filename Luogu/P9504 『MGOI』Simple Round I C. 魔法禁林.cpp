/**
 * @file    P9504 『MGOI』Simple Round I | C. 魔法禁林.cpp
 * @author  ForgotDream
 * @brief   Dijkstra
 * @date    2023-10-02
 */
#include <cstring>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

using i64 = long long;
using pii = std::pair<int, int>;
using ti3 = std::tuple<int, int, int>;

constexpr int N = 2e4 + 50, W = 102;
int n, m, s, t;
std::vector<pii> adj[N];
int dis[W][N];
bool vis[W][N];
void solve() {
  std::cin >> n >> m >> s >> t;
  for (int i = 1; i <= m; i++) {
    int u, v, w;
    std::cin >> u >> v >> w;
    adj[u].emplace_back(v, w);
    adj[v].emplace_back(u, w);
  }
  std::priority_queue<ti3, std::vector<ti3>, std::greater<>> pq;
  std::memset(dis, 0x3f, sizeof(dis));
  pq.emplace(0, 0, t), dis[0][t] = 0;
  while (!pq.empty()) {
    auto [_, k, u] = pq.top();
    pq.pop();
    if (vis[k][u]) continue;
    vis[k][u] = true;
    for (auto [v, w] : adj[u]) {
      int l = std::min(101, k + 1);
      if (dis[l][v] > dis[k][u] + w / l) {
        dis[l][v] = dis[k][u] + w / l;
        pq.emplace(dis[l][v], l, v);
      }
    }
  }
  int ans = 1e9;
  for (int i = 1; i <= 101; i++) {
    if (!vis[i][s]) continue;
    ans = std::min(ans, dis[i][s]);
  }
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
