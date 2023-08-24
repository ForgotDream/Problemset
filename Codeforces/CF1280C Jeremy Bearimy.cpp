/**
 * @file    CF1280C Jeremy Bearimy.cpp
 * @author  ForgotDream
 * @brief   Tree Theory
 * @date    2023-08-24
 */
#include <algorithm>
#include <iostream>

using i64 = long long;
using pii = std::pair<int, int>;

constexpr int N = 2e5 + 50;
int n;
std::vector<pii> adj[N];
i64 G, B, siz[N];
void init() {
  for (int i = 1; i <= 2 * n; i++) adj[i].clear();
  G = B = 0;
}
void dfs(int u, int frm) {
  siz[u] = 1;
  for (auto [v, w] : adj[u]) {
    if (v == frm) continue;
    dfs(v, u);
    siz[u] += siz[v];
    if (siz[v] % 2) G += w;
    B += 1ll * std::min(siz[v], 2 * n - siz[v]) * w;
  }
}
void solve() {
  std::cin >> n;
  init();
  for (int i = 1, u, v, w; i < 2 * n; i++) {
    std::cin >> u >> v >> w;
    adj[u].emplace_back(v, w);
    adj[v].emplace_back(u, w);
  }
  dfs(1, 0);
  std::cout << G << " " << B << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}