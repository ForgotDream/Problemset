/**
 * @file    CF427C Checkposts.cpp
 * @author  ForgotDream
 * @brief   SCC
 * @date    2023-08-29
 */
#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using i64 = long long;

constexpr int N = 1e5 + 50, mod = 1e9 + 7;
int n, m, a[N];
std::vector<int> adj[N];
int dfn[N], low[N], clk;
std::stack<int> s;
int scccnt;
bool ins[N];
std::vector<int> scc[N];
void dfs(int u) {
  dfn[u] = low[u] = ++clk, s.push(u), ins[u] = true;
  for (auto v : adj[u]) {
    if (!dfn[v]) {
      dfs(v);
      low[u] = std::min(low[u], low[v]);
    } else if (ins[v]) {
      low[u] = std::min(low[u], dfn[v]);
    }
  }
  if (dfn[u] == low[u]) {
    ++scccnt;
    int p;
    do {
      p = s.top(), s.pop();
      scc[scccnt].push_back(a[p]), ins[p] = false;
    } while (p != u);
  }
}
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  std::cin >> m;
  for (int i = 1, u, v; i <= m; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v);
  }
  for (int i = 1; i <= n; i++) {
    if (!dfn[i]) dfs(i);
  }
  i64 cost = 0, cnt = 1;
  for (int i = 1; i <= scccnt; i++) {
    auto min = *std::min_element(scc[i].begin(), scc[i].end());
    cost += min;
    (cnt *= std::count(scc[i].begin(), scc[i].end(), min)) %= mod;
  }
  std::cout << cost << " " << cnt << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}