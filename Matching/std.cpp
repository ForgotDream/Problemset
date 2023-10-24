/**
 * @file
 * @author  ForgotDream
 * @brief
 * @date    2023-10-05
 */
#include <cassert>
#include <cstring>
#include <iostream>
#include <vector>
#include <tuple>

using i64 = long long;
using ti3 = std::tuple<int, int, int>;

constexpr int N = 2e5 + 50, K = 30;
int n, m;
std::vector<int> adj[N];
ti3 q[N];
bool used[N];
int bln[N], val[N], cnt;
void dfs(int u) {
  bln[u] = cnt, val[cnt] += (u > n);
  for (auto v : adj[u]) {
    if (bln[v]) continue;
    dfs(v);
  }
}
void solve() {
  std::cin >> n >> m;
  for (int i = 1, u, v, w; i <= m; i++) {
    std::cin >> u >> v >> w;
    q[i] = std::tuple(u, v, w);
  }
  i64 sum = 0;
  for (int _ = 0; _ < K; _++) {
    for (int i = 1; i <= cnt; i++) val[i] = 0, used[i] = false;
    for (int i = 1; i <= 2 * n; i++) bln[i] = 0, adj[i].clear();
    for (int i = 1; i <= m; i++) {
      auto [u, v, w] = q[i];
      if (w & (1ll << _)) {
        adj[u].push_back(v + n), adj[v].push_back(u + n);
        adj[u + n].push_back(v), adj[v + n].push_back(u);
      } else {
        adj[u].push_back(v), adj[v].push_back(u);
        adj[u + n].push_back(v + n), adj[v + n].push_back(u + n);
      }
    }
    cnt = 0;
    for (int i = 1; i <= 2 * n; i++) {
      if (!bln[i]) cnt++, dfs(i);
    }
    for (int i = 1; i <= n; i++) {
      if (bln[i] == bln[i + n]) {
        std::cout << -1 << "\n";
        return;
      }
      if (used[bln[i]] || used[bln[i + n]]) continue;
      sum += (1ll << _) * std::min(val[bln[i]], val[bln[i + n]]);
      used[bln[i]] = used[bln[i + n]] = true;
    }
  }
  std::cout << sum << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
