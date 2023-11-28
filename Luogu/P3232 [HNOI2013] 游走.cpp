/**
 * @file    P3232 [HNOI2013] 游走.cpp
 * @author  ForgotDream
 * @brief   Gauss Jordan + DP
 * @date    2023-11-22
 */
#include <bits/stdc++.h>

using i64 = int64_t;
using f64 = double;

constexpr int N = 505, M = 2e5 + 50;
int n, m;
int st[M], ed[M];
std::vector<int> adj[N];
int deg[N];
f64 mat[N][N], f[M];
void gaussJordan() {
  for (int i = 1; i < n; i++) {
    int p = i;
    for (int j = i + 1; j < n; j++) {
      if (std::abs(mat[j][i]) > std::abs(mat[p][i])) p = j;
    }
    std::swap(p, i);
    auto t = mat[i][i];
    for (int j = i; j <= n; j++) mat[i][j] /= t;
    for (int j = 1; j < n; j++) {
      if (i == j) continue;
      t = mat[j][i] / mat[i][i];
      for (int k = 1; k <= n; k++) mat[j][k] -= mat[i][k] * t;
    }
  }
}
void solve() {
  std::cin >> n >> m;
  for (int i = 1, u, v; i <= m; i++) {
    std::cin >> u >> v;
    st[i] = u, ed[i] = v;
    adj[u].push_back(v), adj[v].push_back(u);
    deg[u]++, deg[v]++;
  }
  mat[1][n] = -1;
  for (int i = 1; i < n; i++) {
    mat[i][i] = -1;
    for (auto j : adj[i]) {
      if (j == n) continue;
      mat[i][j] += 1. / deg[j];
    }
  }
  gaussJordan();
  for (int i = 1; i <= m; i++) {
    int u = st[i], v = ed[i];
    if (u != n) f[i] += mat[u][n] / deg[u];
    if (v != n) f[i] += mat[v][n] / deg[v];
  }
  std::sort(f + 1, f + m + 1, std::greater<>());
  f64 ans = 0;
  for (int i = 1; i <= m; i++) ans += i * f[i];
  std::cout << std::fixed << std::setprecision(3) << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
