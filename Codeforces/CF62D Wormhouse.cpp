/**
 * @file    CF62D Wormhouse.cpp
 * @author  ForgotDream
 * @brief   Euler Tour
 * @date    2023-09-02
 */
#include <algorithm>
#include <iostream>
#include <vector>

using i64 = long long;
using pii = std::pair<int, int>;

constexpr int N = 105, M = 2050;
int n, m, a[M];
std::vector<pii> adj[N];
bool ins[M], flg, bfr[N];
int a[M];
void dfs(int u, int idx) {
  a[idx] = u;
  if (idx == m + 1) {
    if (flg) {
      for (int i = 1; i <= m + 1; i++) std::cout << a[i] << " \n"[i == m + 1];
      exit(0);
    }
    return;
  }
  if (!bfr[u]) std::sort(adj[u].begin(), adj[u].end()), bfr[u] = true;
  for (auto [v, i] : adj[u]) {
    if (ins[i] || (v < a[idx + 1] && !flg)) continue;
    bool fir = false;
    if (v > a[idx + 1] && !flg) flg = true, fir = true;
    ins[i] = true;
    dfs(v, idx + 1);
    ins[i] = false;
    if (fir) flg = false;
  }
}
void solve() {
  std::cin >> n >> m;
  for (int i = 1; i <= m + 1; i++) {
    std::cin >> a[i];
    if (i > 1) {
      adj[a[i]].emplace_back(a[i - 1], i);
      adj[a[i - 1]].emplace_back(a[i], i);
    }
  }
  dfs(a[1], 1);
  std::cout << "No solution\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}