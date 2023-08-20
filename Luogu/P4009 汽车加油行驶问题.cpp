/**
 * @file    P4009 汽车加油行驶问题.cpp
 * @author  ForgotDream
 * @brief   SSSP
 * @date    2023-08-18
 */
#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>

using i64 = long long;
using pii = std::pair<int, int>;

constexpr int N = 2e5 + 50;
constexpr int d[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
std::vector<pii> adj[N];
int cost[4];
int n, K, A, B, C;

// grid graph
int encode(int i, int j, int k) {
  return (i - 1) * n * (K + 1) + (j - 1) * (K + 1) + k;
}
bool valid(int i, int j) { return 1 <= i && i <= n && 1 <= j && j <= n; }

// dijkstra
bool vis[N];
int dis[N];
void addEdge(int u, int v, int w) {
  adj[u].emplace_back(v, w);
}
void dijkstra(int s) {
  std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;
  std::memset(dis, 0x3f, sizeof(dis));
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

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n >> K >> A >> B >> C;
  cost[1] = B, cost[3] = B;

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      int u;
      std::cin >> u;
      for (int k = 0; k < K; k++) {
        addEdge(encode(i, j, k), encode(i, j, k + 1), 0);
      }
      if (u) {
        for (int k = 1; k <= K; k++) {
          addEdge(encode(i, j, k), encode(i, j, 0), A);
        }
        for (int t = 0; t < 4; t++) {
          int dx = i + d[t][0], dy = j + d[t][1];
          if (!valid(dx, dy)) continue;
          addEdge(encode(i, j, 0), encode(dx, dy, 1), cost[t]);
        }
      } else {
        for (int k = 0; k < K; k++) {
          for (int t = 0; t < 4; t++) {
            int dx = i + d[t][0], dy = j + d[t][1];
            if (!valid(dx, dy)) continue;
            addEdge(encode(i, j, k), encode(dx, dy, k + 1), cost[t]);
          }
        }
        for (int k = 1; k <= K; k++) {
          addEdge(encode(i, j, k), encode(i, j, 0), A + C);
        }
      }
    }
  }
  dijkstra(0);

  int ans = 1e9;
  for (int i = 0; i <= K; i++) ans = std::min(ans, dis[encode(n, n, i)]);
  std::cout << ans << "\n";

  return 0;
}