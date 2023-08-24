/**
 * @file    CF1010D Mars rover.cpp
 * @author  ForgotDream
 * @brief   Tree Theory
 * @date    2023-08-24
 */
#include <iostream>
#include <string>
#include <vector>

using i64 = long long;

constexpr int N = 1e6 + 50;
int n;
int adj[N][2], val[N], typ[N];
bool tag[N];
int dfs(int u) {
  if (typ[u] == 0) return val[u];
  if (typ[u] == 1) val[u] = dfs(adj[u][0]) & dfs(adj[u][1]);
  else if (typ[u] == 2) val[u] = dfs(adj[u][0]) | dfs(adj[u][1]);
  else if (typ[u] == 3) val[u] = dfs(adj[u][0]) ^ dfs(adj[u][1]);
  else if (typ[u] == 4) val[u] = !dfs(adj[u][0]);
  if (typ[u] == 1) {
    if (!val[adj[u][0]]) tag[adj[u][1]] = true;
    if (!val[adj[u][1]]) tag[adj[u][0]] = true;
  }
  if (typ[u] == 2) {
    if (val[adj[u][0]]) tag[adj[u][1]] = true;
    if (val[adj[u][1]]) tag[adj[u][0]] = true;
  }
  return val[u];
}
void dfs2(int u) {
  for (auto v : adj[u]) {
    if (!v) break;
    tag[v] |= tag[u];
    dfs2(v);
  }
}
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) {
    std::string s;
    int u, v;
    std::cin >> s;
    if (s == "AND") {
      std::cin >> u >> v, adj[i][0] = u, adj[i][1] = v, typ[i] = 1;
    } else if (s == "OR") {
      std::cin >> u >> v, adj[i][0] = u, adj[i][1] = v, typ[i] = 2;
    } else if (s == "XOR") {
      std::cin >> u >> v, adj[i][0] = u, adj[i][1] = v, typ[i] = 3;
    } else if (s == "NOT") {
      std::cin >> u, adj[i][0] = u, typ[i] = 4;
    } else {
      std::cin >> val[i];
    }
  }
  dfs(1), dfs2(1);
  for (int i = 1; i <= n; i++) {
    if (typ[i]) continue;
    if (tag[i]) std::cout << val[1];
    else std::cout << !val[1];
  }
  std::cout << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}