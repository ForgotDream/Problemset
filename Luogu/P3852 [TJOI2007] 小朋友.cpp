/*
 * @file    P3852 [TJOI2007] 小朋友.cpp
 * @author  ForgotDream
 * @brief   String Graph
 * @date    2024-01-23
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 205;

int n, m;
std::vector<int> adj[N];

// `f` 为完美消除序列
int deg[N], f[N], cur = 1;
bool vis[N];
std::vector<int> deg_bln[N];

void solve() {
  std::cin >> n >> m;
  for (int i = 1, u, v; i <= m; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
  }

  for (int i = 1; i <= n; i++) deg_bln[0].push_back(i);
  for (int i = 1; i <= n; i++) {
    bool flg = false;
    int p = 0;
    while (!flg) {
      for (u32 j = deg_bln[cur].size() - 1; ~j; j--) {
        if (!vis[deg_bln[cur][j]]) {
          p = deg_bln[cur][j], flg = true;
          break;
        } else {
          deg_bln[cur].pop_back();
        }
      }
      if (!flg) cur--;
    }
    f[i] = p, vis[p] = true;
    for (auto v : adj[p]) {
      if (!vis[v]) {
        deg_bln[++deg[v]].push_back(v);
        cur = std::max(cur, deg[v]);
      }
    }
  }

  std::fill(vis + 1, vis + n + 1, false);
  int ans = 0;
  for (int i = n; i; i--) {
    if (vis[f[i]]) continue;
    ans++, vis[f[i]] = true;
    for (auto v : adj[f[i]]) vis[v] = true;
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
