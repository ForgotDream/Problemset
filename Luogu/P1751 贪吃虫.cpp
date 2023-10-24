/**
 * @file    P1751 贪吃虫.cpp
 * @author  ForgotDream
 * @brief   DFS
 * @date    2023-10-02
 */
#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

using i64 = long long;

constexpr int N = 5050, K = 1050, inf = 1e9;
int n, k, h;
std::vector<int> adj[N];
int pos[K], idx[N];
int conq[N], tim[N], vis[K];
int ans[K];
void dfs1(int u, int frm) {
  if (idx[u]) conq[u] = idx[u], tim[u] = 0;
  else conq[u] = tim[u] = inf;
  for (auto v : adj[u]) {
    if (v == frm) continue;
    dfs1(v, u);
    if (tim[v] + 1 < tim[u] || (tim[v] + 1 == tim[u] && conq[v] < conq[u])) {
      tim[u] = tim[v] + 1, conq[u] = conq[v];
    }
  }
}
void dfs2(int u, int frm) {
  if (tim[u] != inf) {
    if (vis[conq[u]] == -1 && conq[u] != conq[frm]) {
      vis[conq[u]] = std::min({vis[conq[frm]], tim[u], tim[frm]});
    } 
    if (vis[conq[u]] != -1 && vis[conq[u]] == tim[u]) {
      pos[conq[u]] = u;
    }
  }
  for (auto v : adj[u]) {
    if (v == frm) continue;
    dfs2(v, u);
  }
}
void solve() {
  std::cin >> n;
  for (int i = 1, u, v; i < n; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
  }
  std::cin >> k;
  for (int i = 1; i <= k; i++) std::cin >> pos[i], idx[pos[i]] = i;
  std::cin >> h;
  for (int i = 1, u; i <= h; i++) {
    std::memset(conq, 0, sizeof(conq));
    std::memset(tim, 0, sizeof(conq));
    std::memset(vis, -1, sizeof(vis));
    std::cin >> u, dfs1(u, 0);
    ans[conq[u]]++, vis[conq[u]] = tim[u];
    dfs2(u, 0);
    std::memset(idx, 0, sizeof(idx));
    for (int i = 1; i <= k; i++) idx[pos[i]] = i;
  }
  for (int i = 1; i <= k; i++) std::cout << pos[i] << " " << ans[i] << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
