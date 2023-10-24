/**
 * @file    CF920E Connected Components?.cpp
 * @author  ForgotDream
 * @brief   Ad Hoc
 * @date    2023-08-27
 */
#include <algorithm>
#include <cstring>
#include <iostream>
#include <numeric>
#include <vector>

using i64 = long long;

constexpr int N = 2e5 + 50;
namespace DSU {
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
  void set(int u, int v) { fa[u] = v; }
} dsu;
}  // namespace DSU
int n, m, deg[N];
std::vector<int> adj[N];
bool ans[N], vis[N];
int bln[N], siz[N], clk;
void solve() {
  std::cin >> n >> m;
  for (int i = 1, u, v; i <= m; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
    deg[u]++, deg[v]++;
  }
  int p = std::min_element(deg + 1, deg + n + 1) - deg;
  ans[p] = true;
  for (auto v : adj[p]) ans[v] = true;
  for (int i = 1; i <= n; i++) {
    if (ans[i]) continue;
    DSU::dsu.set(i, p);
  }
  for (int i = 1; i <= n; i++) {
    if (!ans[i]) continue;
    std::memset(vis, 0, sizeof(vis));
    int fa = DSU::dsu.find(i);
    for (auto v : adj[i]) vis[v] = true;
    for (int j = 1; j <= n; j++) {
      if (vis[j]) continue;
      // DSU::dsu.merge(j, fa);
      DSU::dsu.merge(j, fa);
    }
  }
  for (int i = 1; i <= n; i++) {
    if (DSU::dsu.fa[i] == i) bln[i] = ++clk;
  }
  for (int i = 1; i <= n; i++) siz[bln[DSU::dsu.find(i)]]++;
  std::sort(siz + 1, siz + clk + 1);
  std::cout << clk << "\n";
  for (int i = 1; i <= clk; i++) std::cout << siz[i] << " \n"[i == n];
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}