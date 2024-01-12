/*
 * @file    P3403 跳楼机.cpp
 * @author  ForgotDream
 * @brief   同余最短路
 * @date    2024-01-11
 */
#include <bits/stdc++.h>

using i64 = long long;
using pil = std::pair<int, i64>;
using pli = std::pair<i64, int>;

constexpr int N = 1e5 + 50;

i64 h;
int x, y, z;

std::vector<pil> adj[N];
i64 dis[N];
bool vis[N];

void solve() {
  std::cin >> h >> x >> y >> z;

  if (x == 1 || y == 1 || z == 1) return std::cout << h << "\n", void();

  for (int i = 0; i < x; i++) {
    adj[i].emplace_back((i + y) % x, y);
    adj[i].emplace_back((i + z) % x, z);
  }

  memset(dis, 0x3f, sizeof(dis)), dis[1] = 1;
  std::priority_queue<pli, std::vector<pli>, std::greater<>> pq;
  pq.emplace(1, 1);
  while (!pq.empty()) {
    int u = pq.top().second;
    pq.pop();
    if (vis[u]) continue;
    vis[u] = true;
    for (auto [v, w] : adj[u]) {
      if (dis[u] + w < dis[v]) {
        dis[v] = dis[u] + w;
        pq.emplace(dis[v], v);
      }
    }
  }

  i64 ans = 0;
  for (int i = 0; i < x; i++) {
    if (h >= dis[i]) ans += (h - dis[i]) / x + 1;
  }
  std::cout << ans << "\n";
}

signed main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
