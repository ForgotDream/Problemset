/*
 * @file    P4037 [JSOI2008] 魔兽地图.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2024-01-05
 */
#include <bits/stdc++.h>

using i64 = long long;
using pii = std::pair<int, int>;

constexpr int N = 105, M = 2050;
int n, m, a[N];
bool typ[N];
int pri[N], lim[N];

std::vector<pii> adj[N];
int deg[N];
int f[N][N][M], g[M], ans[M];

bool vis[N];
void dfs(int u) {
  if (vis[u]) return;
  vis[u] = true;
  if (!typ[u]) {
    lim[u] = std::min(lim[u], m / pri[u]);
    for (int i = 0; i <= lim[u]; i++) {
      for (int j = 0; j <= i; j++) {
        f[u][j][i * pri[u]] = (i - j) * a[u];
      }
    }
    return;
  }
  lim[u] = 1e9;
  for (auto [v, w] : adj[u]) {
    dfs(v);
    lim[u] = std::min(lim[v] / w, lim[u]), pri[u] += pri[v] * w;
  }
  lim[u] = std::min(lim[u], m / pri[u]);
  // std::cerr << u << " " << lim[u] << "\n";
  for (int i = 0; i <= lim[u]; i++) {
    memset(g, -0x3f, sizeof(g)), g[0] = 0;
    for (auto [v, w] : adj[u]) {
      for (int j = m; ~j; j--) {
        int tmp = -1e9;
        for (int k = 0; k <= j; k++) {
          tmp = std::max(tmp, g[j - k] + f[v][i * w][k]);
        }
        g[j] = tmp;
      }
    }
    // std::cerr << std::format("{}: ", u);
    // for (int j = 0; j <= m; j++) std::cerr << g[j] << " \n"[j == m];
    for (int j = 0; j <= i; j++) {
      for (int k = 0; k <= m; k++) {
        f[u][j][k] = std::max(f[u][j][k], g[k] + (i - j) * a[u]);
      }
    }
  }
}

void solve() {
  std::cin >> n >> m;
  for (int i = 1, k; i <= n; i++) {
    char c;
    std::cin >> a[i] >> c, typ[i] = (c == 'A');
    if (typ[i]) {
      std::cin >> k;
      for (int u, w; k; k--) {
        std::cin >> u >> w, adj[i].emplace_back(u, w);
        deg[u]++;
      }
    } else {
      std::cin >> pri[i] >> lim[i];
    }
  }

  memset(f, -0x3f, sizeof(f));
  for (int i = 1; i <= n; i++) {
    if (!deg[i]) {
      dfs(i);
      for (int j = m; ~j; j--) {
        for (int k = 0; k <= j; k++) {
          ans[j] = std::max(ans[j], ans[j - k] + f[i][0][k]);
        }
      }
      std::cerr << i << "\n";
    }
  }
  std::cout << ans[m] << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
