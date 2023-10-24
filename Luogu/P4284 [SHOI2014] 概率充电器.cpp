/**
 * @file    P4284 [SHOI2014] 概率充电器.cpp
 * @author  ForgotDream
 * @brief   Math + DP
 * @date    2023-09-20
 */
#include <cstring>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <numeric>
#include <vector>

using i64 = long long;
using f80 = long double;
using pif = std::pair<int, f80>;

constexpr int N = 5e5 + 50;
constexpr f80 eps = 1e-8;
int n;
f80 f[N];
std::vector<pif> adj[N];
void dfs1(int u, int frm) {
  for (auto [v, w] : adj[u]) {
    if (v == frm) continue;
    dfs1(v, u);
    f[u] = f[u] + f[v] * w - f[u] * f[v] * w;
  }
}
void dfs2(int u, int frm) {
  for (auto [v, w] : adj[u]) {
    if (v == frm) continue;
    if (std::fabs(f[v] * w - 1) > eps) {
      f80 tmp = w * (f[u] - f[v] * w) / (1 - f[v] * w);
      f[v] = f[v] + tmp - tmp * f[v];
    }
    dfs2(v, u);
  }
}
void solve() {
  std::cin >> n;
  // init();
  for (int i = 1, u, v, p; i < n; i++) {
    std::cin >> u >> v >> p;
    adj[u].emplace_back(v, 0.01 * p);
    adj[v].emplace_back(u, 0.01 * p);
  }
  for (int i = 1; i <= n; i++) std::cin >> f[i], f[i] *= 0.01;
  dfs1(1, 0), dfs2(1, 0);
  f80 ans = std::accumulate(f + 1, f + n + 1, 0.);
  std::cout << std::fixed << std::setprecision(6) << ans << "\n";
}

signed main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
