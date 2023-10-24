#include <algorithm>
#include <iostream>
#include <vector>

using i64 = long long;
using pil = std::pair<int, i64>;

constexpr int N = 12;
int n, m;
i64 f[N][1 << N];
std::vector<pil> adj[N];
void chkmax(i64 &a, i64 b) { a = a > b ? a : b; }
void solve() {
  std::cin >> n >> m;
  for (int i = 1, u, v, w; i <= m; i++) {
    std::cin >> u >> v >> w;
    adj[u].emplace_back(v, w);
    adj[v].emplace_back(u, w);
  }
  for (int i = 1; i < (1 << n); i++) {
    for (int u = 1; u <= n; u++) {
      if (!(i & (1 << (u - 1)))) continue;
      for (auto [v, w] : adj[u]) {
        if (i & (1 << (v - 1))) continue;
        chkmax(f[v][i | (1 << (v - 1))], f[u][i] + w);
      }
    }
  }
  i64 ans = 0;
  for (int i = 1; i < (1 << n); i++) {
    for (int u = 1; u <= n; u++) {
      if (!(i & (1 << (u - 1)))) continue;
      chkmax(ans, f[u][i]);
    }
  }
  std::cout << ans << "\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}