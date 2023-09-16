/**
 * @file    CF1304E 1-Trees and Queries.cpp
 * @author  ForgotDream
 * @brief   LCA
 * @date    2023-09-08
 */
#include <cmath>
#include <iostream>
#include <vector>

using i64 = long long;

constexpr int N = 2e5 + 50;
int n, q;
std::vector<int> adj[N];
int dep[N], dfn[N], clk, st[20][N];
void dfs(int u, int frm) {
  st[0][dfn[u] = ++clk] = frm, dep[u] = dep[frm] + 1;
  for (auto v : adj[u]) {
    if (v == frm) continue;
    dfs(v, u);
  }
}
int calc(int x, int y) { return dfn[x] < dfn[y] ? x : y; }
int LCA(int u, int v) {
  if (u == v) return u;
  u = dfn[u], v = dfn[v];
  if (u > v) std::swap(u, v);
  int d = std::__lg(v - u++);
  return calc(st[d][u], st[d][v - (1 << d) + 1]);
}
int dis(int u, int v) { return dep[u] + dep[v] - 2 * dep[LCA(u, v)]; }
bool check(int x, int y) { return x <= y && x % 2 == y % 2; }
void solve() {
  std::cin >> n;
  for (int i = 1, u, v; i < n; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
  }
  dfs(1, 0);
  for (int i = 1; i <= std::__lg(n); i++) {
    for (int j = 1; j <= n - (1 << i) + 1; j++) {
      st[i][j] = calc(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
    }
  }
  std::cin >> q;
  while (q--) {
    int x, y, a, b, k;
    std::cin >> x >> y >> a >> b >> k;
    if (check(dis(a, b), k) || check(dis(a, x) + dis(b, y) + 1, k) ||
        check(dis(a, y) + dis(b, x) + 1, k)) {
      std::cout << "YES\n";
    } else {
      std::cout << "NO\n";
    }
  }
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}