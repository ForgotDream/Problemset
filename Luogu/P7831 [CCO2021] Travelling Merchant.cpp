/*
 * @file    P7831 [CCO2021] Travelling Merchant.cpp
 * @author  ForgotDream
 * @brief   Ad Hoc + Topo Sort
 * @date    2024-02-21
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 2e5 + 50, inf = 0x3f3f3f3f;

struct Edge {
  int u, v, r, p;
  friend bool operator<(const Edge &lhs, const Edge &rhs) {
    return lhs. r < rhs.r;
  }
} edges[N];

int n, m;
std::vector<int> adj[N];

std::queue<int> q;
int deg[N], ans[N];
bool vis[N];

void solve() {
  std::cin >> n >> m;
  for (int i = 1, u, v, r, p; i <= m; i++) {
    std::cin >> u >> v >> r >> p;
    edges[i] = {u, v, r, p}, deg[u]++;
  }

  std::sort(edges + 1, edges + m + 1);
  for (int i = 1; i <= m; i++) adj[edges[i].v].push_back(i);

  memset(ans, 0x3f, sizeof(ans));

  for (int i = 1; i <= n; i++) if (!deg[i]) q.push(i);
  for (int i = m; i; i--) {
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (auto p : adj[u]) {
        if (vis[p]) continue;
        vis[p] = true;
        int v = edges[p].u;
        if (!--deg[v]) q.push(v);
        if (ans[u] != inf) {
          ans[v] = std::min(ans[v], std::max(edges[p].r, ans[u] - edges[p].p));
        }
      }
    }
    if (!vis[i]) {
      vis[i] = true;
      int v = edges[i].u;
      if (!--deg[v]) q.push(v);
      ans[v] = std::min(ans[v], edges[i].r);
    }
  }

  for (int i = 1; i <= n; i++) {
    std::cout << (ans[i] == inf ? -1 : ans[i]) << " \n"[i == n];
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
