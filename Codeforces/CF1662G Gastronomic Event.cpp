/**
 * @file    CF1662G Gastronomic Event.cpp
 * @author  ForgotDream
 * @brief   Ad Hoc + DP + Tree Theory
 * @date    2023-11-02
 */
#include <bitset>
#include <iostream>
#include <vector>

using i64 = long long;

constexpr int N = 1e6 + 60;
int n, fa[N];
std::vector<int> adj[N];
int siz[N], msiz[N];
i64 f[N], g[N];
std::bitset<N> b;
int cnt[N];
void dfs(int u) {
  siz[u] = 1;
  for (auto v : adj[u]) {
    dfs(v);
    siz[u] += siz[v], msiz[u] = std::max(msiz[u], siz[v]);
    f[u] += f[v] + siz[v];
  }
  msiz[u] = std::max(msiz[u], n - siz[u]);
}
void dfs2(int u) {
  for (auto v : adj[u]) {
    g[v] = g[u] + n + f[u] - f[v] - 2 * siz[v];
    dfs2(v);
  }
}
void solve() {
  std::cin >> n;
  for (int i = 2; i <= n; i++) {
    std::cin >> fa[i], adj[fa[i]].push_back(i);
  }
  dfs(1), dfs2(1);
  // for (int i = 1; i <= n; i++) std::cerr << f[i] << " " << g[i] << "\n";
  i64 ans = 0;
  for (int i = 1; i <= n; i++) {
    if (msiz[i] <= n / 2) {
      b.reset(), b.set(0);
      for (auto v : adj[i]) cnt[siz[v]]++;
      for (int i = 1; i <= n; i++) {
        if (!cnt[i]) continue;
        for (int k = 1; k <= cnt[i]; k <<= 1) b |= (b << k * i), cnt[i] -= k;
        if (cnt[i]) b |= (b << cnt[i] * i), cnt[i] = 0;
      }
      int p = (n - 1) / 2;
      while (p >= 0 && !b[p]) p--;
      ans = std::max(ans, n + f[i] + g[i] + 1ll * p * (n - 1 - p));
      p = (n - 1) / 2 + 1;
      while (p <= n && !b[p]) p++;
      ans = std::max(ans, n + f[i] + g[i] + 1ll * p * (n - 1 - p));
    } else {
      ans = std::max(ans, n + f[i] + g[i] + 1ll * msiz[i] * (n - 1 - msiz[i]));
    }
  }
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
