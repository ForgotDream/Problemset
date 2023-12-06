/**
 * @file    P3959 [NOIP2017 提高组] 宝藏.cpp
 * @author  ForgotDream
 * @brief   Subset DP
 * @date    2023-12-04
 */
#include <bits/stdc++.h>

using i64 = int64_t;

constexpr int N = 12, inf = 0x3f3f3f3f;
int n, m, adj[N][N];
int f[N][N][1 << N];
inline int siz(int u) { return __builtin_popcount(u); }
void solve() {
  std::cin >> n >> m;
  memset(adj, 0x3f, sizeof(adj));
  for (int i = 1, u, v, w; i <= m; i++) {
    std::cin >> u >> v >> w, u--, v--;
    adj[u][v] = adj[v][u] = std::min(w, adj[v][u]);
  }
  int mask = (1 << n) - 1;
  memset(f, 0x3f, sizeof(f));
  for (int i = 0; i < n; i++) f[n - 1][i][0] = 0;
  for (int d = n - 2; ~d; d--) {
    for (int i = 0; i < n; i++) {
      f[d][i][0] = 0;
      for (int st = 1; st <= mask; st++) {
        if ((st & (1 << i)) || siz(st) > n - d - 1) continue;
        for (int sub = st; sub; sub = (sub - 1) & st) {
          if (f[d][i][st - sub] >= f[d][i][st]) continue;
          for (int k = 0; k < n; k++) {
            if (!(sub & (1 << k)) || adj[i][k] == inf) continue;
            f[d][i][st] = std::min(f[d][i][st], 
                (d + 1) * adj[i][k] + f[d + 1][k][sub - (1 << k)] + f[d][i][st - sub]);
          }
        }
      }
    }
  }
  int ans = inf;
  for (int i = 0; i < n; i++) ans = std::min(ans, f[0][i][mask - (1 << i)]);
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
