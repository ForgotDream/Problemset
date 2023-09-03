/**
 * @file    CF267B Dominoes.cpp
 * @author  ForgotDream
 * @brief   DFS
 * @date    2023-09-02
 */
#include <iostream>
#include <vector>

using i64 = long long;
using pii = std::pair<int, int>;

constexpr int N = 205, M = 10;
int n;
std::vector<pii> adj[M];
bool vis[N];
int convert(int u) { return u > n ? u - n : u; }
int st[N], top;
void dfs(int u, int idx) {
  for (auto [v, i] : adj[u]) {
    if (vis[convert(i)]) continue;
    vis[convert(i)] = true;
    dfs(v, i);
  }
  st[++top] = idx;
}
void solve() {
  std::cin >> n;
  int s = 0;
  for (int i = 1, u, v; i <= n; i++) {
    std::cin >> u >> v;
    adj[u].emplace_back(v, i);
    adj[v].emplace_back(u, i + n);
    s = u;
  }
  if (n == 1) {
    std::cout << 1 << " +\n";
    return;
  }
  for (int i = 0, cnt = 0; i <= 6; i++) {
    if (adj[i].size() % 2) s = i, cnt++;
    if (cnt > 2) {
      std::cout << "No solution\n";
      return;
    }
  }
  dfs(s, 0);
  if (top == n + 1) {
    for (int i = 1; i <= n; i++) {
      if (st[i] > n) std::cout << st[i] - n << " +\n";
      else std::cout << st[i] << " -\n";
    }
    return;
  }
  std::cout << "No solution\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}