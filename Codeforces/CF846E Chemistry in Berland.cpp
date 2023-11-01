/**
 * @file    CF846E Chemistry in Berland.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-11-01
 */
#include <iostream>
#include <vector>

using i64 = long long;
using pii = std::pair<int, int>;
using f80 = long double;

constexpr int N = 1e5 + 50;
int n;
i64 a[N], b[N], x[N], k[N];
std::vector<pii> adj[N];
f80 f[N];
void dfs(int u) {
  f[u] = b[u] - a[u];
  for (auto [v, w] : adj[u]) {
    dfs(v);
    if (f[v] >= 0) f[u] += f[v];
    else f[u] += w * f[v];
  }
}
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> b[i];
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  for (int i = 2, x, k; i <= n; i++) std::cin >> x >> k, adj[x].emplace_back(i, k);
  dfs(1);
  if (f[1] >= 0) std::cout << "YES\n";
  else std::cout << "NO\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
