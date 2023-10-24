/**
 * @file    CF505D Mr. Kitayuta's Technology.cpp
 * @author  ForgotDream
 * @brief   DSU
 * @date    2023-09-03
 */
#include <iostream>
#include <numeric>
#include <queue>
#include <vector>

using i64 = long long;

constexpr int N = 1e5 + 50;
int n, m;
std::vector<int> adj[N];
int deg[N];
struct DSU {
  int fa[N];
  DSU() { std::iota(fa, fa + N, 0); }
  int find(int u) { return u == fa[u] ? u : fa[u] = find(fa[u]); }
  bool merge(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return false;
    fa[u] = v;
    return true;
  }
} dsu;
bool vis[N];
void solve() {
  std::cin >> n >> m;
  for (int i = 1, u, v; i <= m; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), deg[v]++, dsu.merge(u, v);
  }
  int ans = n;
  std::queue<int> q;
  for (int i = 1; i <= n; i++) {
    if (dsu.fa[i] == i) ans--;
    if (!deg[i]) q.push(i);
  }
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (auto v : adj[u]) {
      if (!--deg[v]) q.push(v);
    }
  }
  for (int i = 1; i <= n; i++) {
    if (deg[i]) ans += !vis[dsu.find(i)], vis[dsu.find(i)] = true;
  }
  std::cout << ans << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}