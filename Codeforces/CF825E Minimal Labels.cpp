/**
 * @file    CF825E Minimal Labels.cpp
 * @author  ForgotDream
 * @brief   BFS
 * @date    2023-08-25
 */
#include <iostream>
#include <queue>
#include <vector>

using i64 = long long;

constexpr int N = 1e5 + 50;
int n, m;
std::vector<int> adj[N];
int deg[N], p[N], cnt;
void solve() {
  std::cin >> n >> m;
  for (int i = 1, u, v; i <= m; i++) {
    std::cin >> u >> v;
    adj[v].push_back(u), deg[u]++;
  }
  std::priority_queue<int> pq;
  for (int i = 1; i <= n; i++) {
    if (!deg[i]) pq.push(i);
  }
  while (!pq.empty()) {
    int u = pq.top();
    pq.pop();
    p[u] = ++cnt;
    for (auto v : adj[u]) {
      if (!--deg[v]) pq.push(v);
    }
  }
  for (int i = 1; i <= n; i++) std::cout << n + 1 - p[i] << " \n"[i == n];
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}