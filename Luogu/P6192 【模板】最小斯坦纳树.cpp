/**
 * @file    P6192 【模板】最小斯坦纳树.cpp
 * @author  ForgotDream
 * @brief   Steiner Tree
 * @date    2023-11-29
 */
#include <bits/stdc++.h>

using i64 = int64_t;
using pii = std::pair<int, int>;

constexpr int N = 1050, K = 10, inf = 0x3f3f3f3f;
int n, m, k, a[N];
std::vector<pii> adj[N];
int f[1 << K][N];
bool vis[N];
void dijkstra(int st) {
  std::priority_queue<pii, std::vector<pii>, std::greater<>> pq;
  memset(vis, false, sizeof(vis));
  for (int i = 1; i <= n; i++) {
    if (f[st][i] != inf) pq.emplace(f[st][i], i);
  }
  while (!pq.empty()) {
    int u = pq.top().second;
    pq.pop();
    if (vis[u]) continue;
    vis[u] = true;
    for (auto [v, w] : adj[u]) {
      if (f[st][v] > f[st][u] + w) {
        f[st][v] = f[st][u] + w;
        pq.emplace(f[st][v], v);
      }
    }
  }
}
void solve() {
  std::cin >> n >> m >> k;
  for (int i = 1, u, v, w; i <= m; i++) {
    std::cin >> u >> v >> w;
    adj[u].emplace_back(v, w), adj[v].emplace_back(u, w);
  }
  memset(f, 0x3f, sizeof(f));
  for (int i = 0; i < k; i++) std::cin >> a[i], f[1 << i][a[i]] = 0;
  int mask = (1 << k) - 1;
  for (int st = 1; st <= mask; st++) {
    for (int nxt = st & (st - 1); nxt; nxt = (nxt - 1) & st) {
      if (nxt < (st ^ nxt)) break;
      for (int i = 1; i <= n; i++) {
        f[st][i] = std::min(f[st][i], f[nxt][i] + f[st ^ nxt][i]);
      }
    }
    dijkstra(st);
  }
  std::cout << *std::min_element(f[mask] + 1, f[mask] + n + 1) << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
