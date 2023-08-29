/**
 * @file    P4151 [WC2011] 最大XOR和路径.cpp
 * @author  ForgotDream
 * @brief   Vector Space
 * @date    2023-08-27
 */
#include <iostream>
#include <vector>

using i64 = long long;
using u64 = unsigned long long;
using pil = std::pair<int, i64>;

namespace VECSPACE {
constexpr int N = 64;
u64 p[N];
void insert(u64 val) {
  for (int i = 63; i >= 0; i--) {
    if (!(val & (1ll << i))) continue;
    if (!p[i]) {
      p[i] = val;
      break;
    }
    val ^= p[i];
  }
}
u64 query(u64 val) {
  u64 res = val;
  for (int i = 63; i >= 0; i--) res = std::max(res, res ^ p[i]);
  return res;
}
}  // namespace VECSPACE
constexpr int N = 2e5 + 50;
int n, m;
std::vector<pil> adj[N];
bool vis[N];
u64 dis[N];
void dfs(int u, u64 cur) {
  dis[u] = cur, vis[u] = true;
  for (auto [v, w] : adj[u]) {
    if (!vis[v]) dfs(v, cur ^ w);
    else VECSPACE::insert(cur ^ w ^ dis[v]);
  }
}
void solve() {
  std::cin >> n >> m;
  for (int i = 1, u, v; i <= m; i++) {
    u64 w;
    std::cin >> u >> v >> w;
    adj[u].emplace_back(v, w), adj[v].emplace_back(u, w);
  }
  dfs(1, 0);
  std::cout << VECSPACE::query(dis[n]) << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}