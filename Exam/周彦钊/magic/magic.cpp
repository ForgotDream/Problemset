/**
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2023-08-08
 */
#include <bits/stdc++.h>
using i64 = long long;
using pii = std::pair<int, int>;
constexpr int N = 1e3 + 50, M = 1e5 + 50;
int n, m, q, p[M];
std::vector<pii> adj[500 * N];
i64 dis[500 * N];
bool vis[500 * N];
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
  freopen("magic.in", "r", stdin);
  freopen("magic.out", "w", stdout);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    int u, v, w;
    std::cin >> u >> v >> w;
    for (int j = 1; j <= 500; j++) {
      int g = std::__gcd(j, w);
      adj[u + j * n].emplace_back(v + g * n, w / g);
      adj[v + j * n].emplace_back(u + g * n, w / g);
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= 500; j++) {
      adj[i + j * n].emplace_back(i, 0);
      adj[i].emplace_back(i + j * n, 0);
    }
  }
  dijkstra(n);
  std::cin >> q;
  for (int i = 1; i <= q; i++) {
    std::cin >> p[i];
    std::cout << dis[p[i]] << "\n";
  }
  return 0;
}