#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 3e5 + 50, mod = 998244353;

int n;
std::vector<int> adj[N];

i64 f[N][3];

void dfs(int u, int frm) {
  f[u][0] = f[u][1] = 1;
  for (auto v : adj[u]) {
    if (v == frm) continue;
    dfs(v, u);
    f[u][1] *= (f[v][0] + f[v][1]) % mod;
    f[u][1] %= mod;
    f[u][2] += (f[v][2] + f[v][1]) % mod;
    f[u][2] %= mod;
  }
}

void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) adj[i].clear(), f[i][0] = f[i][1] = f[i][2] = 0;
  for (int i = 1, u, v; i < n; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
  }
  dfs(1, 0);
  std::cout << (f[1][0] + f[1][1] + f[1][2]) % mod << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  std::cin >> t;
  while (t--) solve();

  return 0;
}



