/**
 * @file    CF113D Museum.cpp
 * @author  ForgotDream
 * @brief   Gauss Jordan + DP
 * @date    2023-11-22
 */
#include <bits/stdc++.h>

using i64 = int64_t;
using f64 = double;

constexpr int N = 2550;
int n, m, a, b;
f64 p[N];
std::vector<int> adj[N];
int deg[N], idx[N][N];
f64 mat[N][N];
void gaussJordan(f64 a[N][N]) {
  for (int i = 1; i <= m; i++) {
    int p = i;
    for (int j = i + 1; j <= m; j++) if (std::abs(a[j][i]) > std::abs(a[p][i])) p = j;
    std::swap(a[p], a[i]);
    auto t = a[i][i];
    for (int j = i; j <= m + 1; j++) a[i][j] /= t;
    for (int j = 1; j <= m; j++) {
      if (i == j) continue;
      t = a[j][i] / a[i][i];
      for (int k = 1; k <= m + 1; k++) a[j][k] -= a[i][k] * t;
    }
  }
}
void solve() {
  std::cin >> n >> m >> a >> b;
  for (int i = 1, u, v; i <= m; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
    deg[u]++, deg[v]++;
  }
  for (int i = 1; i <= n; i++) std::cin >> p[i];
  m = 0;
  for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) idx[i][j] = ++m;
  mat[idx[a][b]][m + 1] = -1;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      int piv = idx[i][j];
      mat[piv][piv]--;
      if (i != j) mat[piv][piv] += p[i] * p[j];
      for (auto u : adj[i]) {
        for (auto v : adj[j]) {
          if (u == v) continue;
          mat[piv][idx[u][v]] = ((1 - p[u]) / deg[u]) * ((1 - p[v]) / deg[v]);
        }
      }
      for (auto u : adj[i]) {
        if (u == j) continue;
        mat[piv][idx[u][j]] = ((1 - p[u]) / deg[u]) * p[j];
      }
      for (auto v : adj[j]) {
        if (v == i) continue;
        mat[piv][idx[i][v]] = ((1 - p[v]) / deg[v]) * p[i];
      }
    }
  }
  gaussJordan(mat);
  for (int i = 1; i <= n; i++) {
    std::cout << std::fixed << std::setprecision(10) 
              << mat[idx[i][i]][m + 1] << " \n"[i == n];
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
