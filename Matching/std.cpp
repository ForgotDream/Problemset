#include <bits/stdc++.h>

using i64 = int64_t;

constexpr int N = 1e5 + 50, M = 205, LIM = 200, mod = 998244353;
int n, w[N], q;
i64 f[N][M], g[N][M];
void init() {
  f[0][0] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= LIM; j++) {
      f[i][j] = f[i - 1][j];
      if (j >= w[i]) (f[i][j] += f[i - 1][j - w[i]]) %= mod;
    }
  }
  g[n + 1][0] = 1;
  for (int i = n; i >= 1; i--) {
    for (int j = 0; j <= LIM; j++) {
      g[i][j] = g[i + 1][j];
      if (j >= w[i]) (g[i][j] += g[i + 1][j - w[i]]) %= mod;
    }
  }
}
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> w[i];
  init();
  std::cin >> q;
  for (int l, r, m; q; q--) {
    std::cin >> l >> r >> m;
    i64 tmp = 0;
    for (int i = 1; i < m; i++) (tmp += f[l - 1][i] * g[r + 1][m - i] % mod) %= mod;
    for (int i = 1; i < m; i++) (tmp += (f[r][i] - f[l - 1][i]) * g[r + 1][m - i] % mod) %= mod;
    // for (int i = 1; i < m; i++) (tmp += f[r][i] * g[r + 1][m - i] % mod) %= mod;
    std::cout << (f[n][m] - f[r][m] - g[l][m] - tmp + mod) % mod << "\n";
    std::cout << f[r][m] << " " << g[l][m] << " " << f[n][m] << " " << tmp << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
